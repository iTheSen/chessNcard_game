#include "views/GameView.h"

#include <new>

#include "utils/LayoutConstants.h"
#include "utils/UiTextFactory.h"

namespace qipai {

GameView* GameView::create()
{
    GameView* view = new (std::nothrow) GameView();
    if (view == nullptr) {
        return nullptr;
    }

    if (!view->init()) {
        delete view;
        return nullptr;
    }

    view->autorelease();
    return view;
}

bool GameView::init()
{
    if (!Layer::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(layout::kDesignWidth, layout::kDesignHeight));

    _playFieldView = PlayFieldView::create();
    if (_playFieldView == nullptr) {
        return false;
    }
    addChild(_playFieldView, 1);

    _stackView = StackView::create();
    if (_stackView == nullptr) {
        return false;
    }
    addChild(_stackView, 2);

    cocos2d::LayerColor* statusPanel = cocos2d::LayerColor::create(
        cocos2d::Color4B(11, 25, 40, 190),
        layout::kDesignWidth - 28.0f,
        84.0f);
    if (statusPanel == nullptr) {
        return false;
    }
    statusPanel->setIgnoreAnchorPointForPosition(false);
    statusPanel->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    statusPanel->setPosition(cocos2d::Vec2(layout::kDesignWidth * 0.5f, layout::kStackHeight - 56.0f));
    addChild(statusPanel, 4);

    cocos2d::DrawNode* statusBorder = cocos2d::DrawNode::create();
    statusBorder->drawRect(
        cocos2d::Vec2::ZERO,
        statusPanel->getContentSize(),
        cocos2d::Color4F(0.88f, 0.95f, 1.0f, 0.72f));
    statusPanel->addChild(statusBorder, 0);

    _statusLabel = ui::createLabel("", 30.0f, cocos2d::Color3B(230, 241, 255), false);
    if (_statusLabel == nullptr) {
        return false;
    }
    _statusLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 0.5f));
    _statusLabel->setPosition(cocos2d::Vec2(18.0f, statusPanel->getContentSize().height * 0.5f));
    _statusLabel->setWidth(statusPanel->getContentSize().width - 36.0f);
    _statusLabel->setOverflow(cocos2d::Label::Overflow::SHRINK);
    statusPanel->addChild(_statusLabel, 1);

    _stackView->setUndoCallback([this]() {
        if (_onUndoClickCallback != nullptr) {
            _onUndoClickCallback();
        }
    });

    return true;
}

void GameView::setOnCardClickCallback(const std::function<void(int)>& callback)
{
    _onCardClickCallback = callback;
}

void GameView::setOnUndoClickCallback(const std::function<void()>& callback)
{
    _onUndoClickCallback = callback;
}

void GameView::buildCards(const GameModel& gameModel)
{
    clearCards();

    const std::vector<int> allCardIds = gameModel.getAllCardIds();
    for (int cardId : allCardIds) {
        const CardModel* cardModel = gameModel.findCard(cardId);
        if (cardModel == nullptr) {
            continue;
        }

        CardView* cardView = CardView::create(*cardModel);
        if (cardView == nullptr) {
            continue;
        }

        cardView->setOnClickCallback([this](int clickedCardId) {
            if (_onCardClickCallback != nullptr) {
                _onCardClickCallback(clickedCardId);
            }
        });

        addChild(cardView, 10);
        _cardViews[cardId] = cardView;
    }
}

CardView* GameView::getCardView(int cardId) const
{
    auto iter = _cardViews.find(cardId);
    if (iter == _cardViews.end()) {
        return nullptr;
    }
    return iter->second;
}

void GameView::setCardVisible(int cardId, bool visible)
{
    CardView* cardView = getCardView(cardId);
    if (cardView != nullptr) {
        cardView->setVisible(visible);
    }
}

void GameView::setCardInteraction(int cardId, bool enabled)
{
    CardView* cardView = getCardView(cardId);
    if (cardView != nullptr) {
        cardView->setInteractionEnabled(enabled);
    }
}

void GameView::setCardPosition(int cardId, const cocos2d::Vec2& position)
{
    CardView* cardView = getCardView(cardId);
    if (cardView != nullptr) {
        cardView->setPosition(position);
    }
}

void GameView::setCardZOrder(int cardId, int zOrder)
{
    CardView* cardView = getCardView(cardId);
    if (cardView != nullptr) {
        cardView->setLocalZOrder(zOrder);
    }
}

void GameView::moveCard(int cardId, const cocos2d::Vec2& targetPosition, float duration, const std::function<void()>& onComplete)
{
    CardView* cardView = getCardView(cardId);
    if (cardView == nullptr) {
        if (onComplete != nullptr) {
            onComplete();
        }
        return;
    }

    cardView->moveTo(targetPosition, duration, onComplete);
}

cocos2d::Vec2 GameView::getTrayCardPosition() const
{
    return layout::trayCardPosition();
}

cocos2d::Vec2 GameView::getStackCardPosition() const
{
    return layout::stackCardPosition();
}

void GameView::setStatusText(const std::string& text)
{
    if (_statusLabel != nullptr) {
        _statusLabel->setString(text);
    }
}

void GameView::clearCards()
{
    for (auto& pair : _cardViews) {
        if (pair.second != nullptr) {
            pair.second->removeFromParent();
        }
    }
    _cardViews.clear();
}

} // namespace qipai
