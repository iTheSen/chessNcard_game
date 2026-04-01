#include "controllers/GameController.h"

#include <algorithm>
#include <sstream>
#include <vector>

#include "configs/loaders/LevelConfigLoader.h"
#include "configs/models/CardResConfig.h"
#include "services/GameRuleService.h"
#include "services/GameModelFromLevelGenerator.h"
#include "utils/LayoutConstants.h"

namespace qipai {


// 初始化当前总视图_gameView利用Resources下的 关卡json数据。
bool GameController::init(GameView* gameView, const std::string& levelConfigPath)
{
    if (gameView == nullptr) {
        return false;
    }

    _gameView = gameView;
    // MVC 模型视图控制器 设置回调
    _gameView->setOnCardClickCallback([this](int cardId) {
        //通过this传递的GameController 调用handlerCardClick
        handleCardClick(cardId);
    });
    _gameView->setOnUndoClickCallback([this]() {
        handleUndoClick();
    });

    _levelConfigPaths.clear();
    //FileUtil的工作目录为 _searchPathArray 下的目录 初始化init会自动push_back _defaultResRootPath
    cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
    // 使用cocos提供的API遍历关卡json串
    // 目前最多99关
    for (int i = 1; i <= 99; ++i) {
        const std::string candidate = cocos2d::StringUtils::format("configs/levels/level_%d.json", i);
        if (!fileUtils->isFileExist(candidate)) {
            break;
        }
        _levelConfigPaths.push_back(candidate);
    }

    if (_levelConfigPaths.empty()) {
        _levelConfigPaths.push_back(levelConfigPath);
    }

    _currentLevelIndex = 0;
    for (size_t i = 0; i < _levelConfigPaths.size(); ++i) {
        if (_levelConfigPaths[i] == levelConfigPath) {
            _currentLevelIndex = static_cast<int>(i);
            break;
        }
    }

    // 这里会调 buildCards,本函数在return前已经设置了 _gameview的点击回调了
    // 设置的是自己的 handleCardClick. 调loadLevelByIndex会在gameview 里 
    // buildCards buildCards 会设置
    return loadLevelByIndex(_currentLevelIndex);
}

// 处理点击
void GameController::handleCardClick(int cardId)
{
    if (_isAnimating) {
        return;
    }

    UndoModel undoRecord;
    std::string error;
    if (!resolveCardClick(cardId, undoRecord, error)) {
        if (!error.empty()) {
            refreshStatusText(error);
        }
        return;
    }

    _isAnimating = true;
    _gameView->setCardVisible(cardId, true);
    _gameView->setCardInteraction(cardId, false);
    // 设置最高的 ZOrder 避免移动的过程被别的牌盖住
    _gameView->setCardZOrder(cardId, 4000);

    _gameView->moveCard(cardId, _gameView->getTrayCardPosition(), layout::kCardMoveDuration, [this, undoRecord]() {
        _undoManager.pushRecord(undoRecord);
        _isAnimating = false;
        refreshViewFromModel();

        if (undoRecord.getActionType() == UAT_STACK_TO_TRAY) {
            refreshStatusText(u8"\u5DF2\u4ECE\u5907\u7528\u724C\u5806\u66FF\u6362\u9876\u90E8\u624B\u724C");
        } else {
            refreshStatusText(u8"\u5339\u914D\u6210\u529F\u5E76\u66FF\u6362\u9876\u90E8\u624B\u724C");
        }

        handleLevelProgressAfterAction();
    });
}

bool GameController::resolveCardClick(int cardId, UndoModel& outUndo, std::string& outError)
{
    CardModel* clickedCard = _gameModel.findCard(cardId);
    if (clickedCard == nullptr) {
        return false;
    }

    const int nextStackCardId = _gameModel.peekNextStackCardId();
    if (clickedCard->getZone() == CZT_STACK && cardId == nextStackCardId) {
        if (hasOperablePlayFieldMatch()) {
            outError = u8"\u4E3B\u724C\u533A\u4ECD\u6709\u53EF\u5339\u914D\u5361\u724C\uFF0C\u8BF7\u5148\u5339\u914D";
            return false;
        }

        return _stackController.handleStackCardClick(
            _gameModel,
            _gameView->getStackCardPosition(),
            _gameView->getTrayCardPosition(),
            outUndo,
            outError);
    }

    if (clickedCard->getZone() == CZT_PLAYFIELD) {
        return _playFieldController.handleCardClick(
            _gameModel,
            cardId,
            _gameView->getTrayCardPosition(),
            outUndo,
            outError);
    }

    return false;
}

void GameController::handleUndoClick()
{
    if (_isAnimating) {
        return;
    }

    UndoModel undoRecord;
    if (!_undoManager.popRecord(undoRecord)) {
        refreshStatusText(u8"\u5F53\u524D\u6CA1\u6709\u53EF\u56DE\u9000\u8BB0\u5F55");
        return;
    }

    _isAnimating = true;
    const int movedCardId = undoRecord.getMovedCardId();
    _gameView->setCardVisible(movedCardId, true);
    _gameView->setCardInteraction(movedCardId, false);
    // 回退也和点击类似，保证显示在顶层
    _gameView->setCardZOrder(movedCardId, 4000);

    _gameView->moveCard(movedCardId, undoRecord.getSourcePosition(), layout::kCardMoveDuration, [this, undoRecord]() {
        applyUndoRecord(undoRecord);
        _isAnimating = false;
        refreshViewFromModel();
        refreshStatusText(u8"\u56DE\u9000\u6210\u529F");
    });
}

// 刷新 Model（GameModel)的views
void GameController::refreshViewFromModel()
{
    const int trayTopCardId = _gameModel.getTrayTopCardId();
    const int nextStackCardId = _gameModel.peekNextStackCardId();
    rebuildOperablePlayFieldCardIds();

    std::vector<int> cardIds = _gameModel.getAllCardIds();
    for (int cardId : cardIds) {
        refreshSingleCardView(cardId, trayTopCardId, nextStackCardId);
    }
}

void GameController::refreshSingleCardView(int cardId, int trayTopCardId, int nextStackCardId)
{
    CardModel* card = _gameModel.findCard(cardId);
    if (card == nullptr) {
        return;
    }

    // 主牌区用 1000～2500 ZOrder 的桶
    if (card->getZone() == CZT_PLAYFIELD) {
        const bool isOperable = _operablePlayFieldCardIds.find(cardId) != _operablePlayFieldCardIds.end();
        _gameView->setCardVisible(cardId, true);
        _gameView->setCardInteraction(cardId, isOperable);
        _gameView->setCardPosition(cardId, card->getCurrentPosition());
        // 设置渲染顺序 LocalZOrder
        _gameView->setCardZOrder(cardId, 1000 + static_cast<int>(card->getCurrentPosition().y));
        return;
    }

    // 备用牌
    if (card->getZone() == CZT_STACK) {
        card->setCurrentPosition(_gameView->getStackCardPosition());
        const bool isCurrentStackCard = (cardId == nextStackCardId);
        _gameView->setCardVisible(cardId, isCurrentStackCard);
        _gameView->setCardInteraction(cardId, isCurrentStackCard);
        _gameView->setCardPosition(cardId, _gameView->getStackCardPosition());
        _gameView->setCardZOrder(cardId, 2500);
        return;
    }
    // 手牌区
    if (card->getZone() == CZT_TRAY) {
        card->setCurrentPosition(_gameView->getTrayCardPosition());
        const bool isTrayTop = (cardId == trayTopCardId);
        _gameView->setCardVisible(cardId, isTrayTop);
        _gameView->setCardInteraction(cardId, false);
        _gameView->setCardPosition(cardId, _gameView->getTrayCardPosition());
        _gameView->setCardZOrder(cardId, 3000);
        return;
    }

    _gameView->setCardVisible(cardId, false);
    _gameView->setCardInteraction(cardId, false);
}

void GameController::rebuildOperablePlayFieldCardIds()
{
    _operablePlayFieldCardIds.clear();

    std::vector<const CardModel*> playFieldCards;
    const std::vector<int>& playFieldCardIds = _gameModel.getPlayFieldCardIds();
    playFieldCards.reserve(playFieldCardIds.size());

    for (int cardId : playFieldCardIds) {
        const CardModel* card = _gameModel.findCard(cardId);
        if (card != nullptr && card->getZone() == CZT_PLAYFIELD) {
            playFieldCards.push_back(card);
        }
    }

    std::sort(playFieldCards.begin(), playFieldCards.end(), [](const CardModel* left, const CardModel* right) {
        return left->getCurrentPosition().y > right->getCurrentPosition().y;
    });

    const cocos2d::Size cardSize = CardResConfig::getCardSize();
    const cocos2d::Vec2 half(cardSize.width * 0.5f, cardSize.height * 0.5f);
    std::vector<cocos2d::Rect> higherRects;
    higherRects.reserve(playFieldCards.size());

    for (const CardModel* card : playFieldCards) {
        const cocos2d::Vec2& pos = card->getCurrentPosition();
        const cocos2d::Rect cardRect(pos.x - half.x, pos.y - half.y, cardSize.width, cardSize.height);

        bool isCovered = false;
        for (const cocos2d::Rect& higherRect : higherRects) {
            if (cardRect.intersectsRect(higherRect)) {
                isCovered = true;
                break;
            }
        }

        if (!isCovered) {
            _operablePlayFieldCardIds.insert(card->getCardId());
        }

        higherRects.push_back(cardRect);
    }
}

bool GameController::loadLevelByIndex(int levelIndex)
{
    if (levelIndex < 0 || levelIndex >= static_cast<int>(_levelConfigPaths.size()) || _gameView == nullptr) {
        return false;
    }

    const std::string& levelPath = _levelConfigPaths[levelIndex];
    LevelConfig levelConfig;
    std::string loadError;
    if (!LevelConfigLoader::loadLevelConfig(levelPath, levelConfig, &loadError)) {
        _gameView->setStatusText(std::string(u8"\u5173\u5361\u52A0\u8F7D\u5931\u8D25: ") + loadError);
        return false;
    }

    _currentLevelIndex = levelIndex;
    _gameModel = GameModelFromLevelGenerator::generateGameModel(levelConfig);
    _undoManager.clear();
    _operablePlayFieldCardIds.clear();
    _isAnimating = false;

    _gameView->buildCards(_gameModel);
    refreshViewFromModel();

    std::stringstream stream;
    stream << u8"\u5DF2\u8F7D\u5165\u7B2C " << (_currentLevelIndex + 1) << u8" \u5173\uFF0C\u5F00\u59CB\u6E38\u620F";
    refreshStatusText(stream.str());
    return true;
}

bool GameController::isCurrentLevelCleared() const
{
    const std::vector<int>& playFieldCardIds = _gameModel.getPlayFieldCardIds();
    for (int cardId : playFieldCardIds) {
        const CardModel* card = _gameModel.findCard(cardId);
        if (card != nullptr && card->getZone() == CZT_PLAYFIELD) {
            return false;
        }
    }
    return true;
}

bool GameController::hasOperablePlayFieldMatch() const
{
    const int trayTopCardId = _gameModel.getTrayTopCardId();
    const CardModel* trayTopCard = _gameModel.findCard(trayTopCardId);
    if (trayTopCard == nullptr || trayTopCard->getZone() != CZT_TRAY) {
        return false;
    }

    for (int cardId : _operablePlayFieldCardIds) {
        const CardModel* playFieldCard = _gameModel.findCard(cardId);
        if (playFieldCard == nullptr || playFieldCard->getZone() != CZT_PLAYFIELD) {
            continue;
        }

        if (GameRuleService::canMatch(*playFieldCard, *trayTopCard)) {
            return true;
        }
    }
    return false;
}

void GameController::handleLevelProgressAfterAction()
{
    if (!isCurrentLevelCleared()) {
        return;
    }

    const int nextLevelIndex = _currentLevelIndex + 1;
    if (nextLevelIndex >= static_cast<int>(_levelConfigPaths.size())) {
        refreshStatusText(u8"\u5168\u90E8\u5173\u5361\u5DF2\u5B8C\u6210\uFF0C\u606D\u559C\u901A\u5173\uFF01");
        return;
    }

    std::stringstream stream;
    stream << u8"\u7B2C " << (_currentLevelIndex + 1) << u8" \u5173\u5DF2\u5B8C\u6210\uFF0C\u6B63\u5728\u8FDB\u5165\u7B2C "
           << (nextLevelIndex + 1) << u8" \u5173...";
    refreshStatusText(stream.str());

    _isAnimating = true;
    _gameView->runAction(cocos2d::Sequence::create(
        cocos2d::DelayTime::create(0.5f),
        cocos2d::CallFunc::create([this, nextLevelIndex]() {
            loadLevelByIndex(nextLevelIndex);
        }),
        nullptr));
}

void GameController::applyUndoRecord(const UndoModel& undoRecord)
{
    CardModel* movedCard = _gameModel.findCard(undoRecord.getMovedCardId());
    if (movedCard != nullptr) {
        movedCard->setZone(undoRecord.getSourceZone());
        movedCard->setCurrentPosition(undoRecord.getSourcePosition());
    }

    _gameModel.setTrayTopCardId(undoRecord.getPreviousTrayCardId());
    _gameModel.setNextStackIndex(undoRecord.getPreviousStackIndex());
}

void GameController::refreshStatusText(const std::string& message)
{
    std::stringstream stream;
    stream << message << " | " << u8"\u53EF\u56DE\u9000\u6B65\u6570: " << _undoManager.size();

    if (_gameModel.canDrawFromStack()) {
        stream << " | " << u8"\u5907\u7528\u724C\u5269\u4F59: "
               << static_cast<int>(_gameModel.getStackCardIds().size()) - _gameModel.getNextStackIndex();
    } else {
        stream << " | " << u8"\u5907\u7528\u724C\u5269\u4F59: 0";
    }

    if (_gameView != nullptr) {
        _gameView->setStatusText(stream.str());
    }
}

} // namespace qipai
