#include "controllers/PlayFieldController.h"

#include "services/GameRuleService.h"

namespace qipai {

bool PlayFieldController::handleCardClick(
    GameModel& gameModel,
    int cardId,
    const cocos2d::Vec2& trayPosition,
    UndoModel& outUndo,
    std::string& outError) const
{
    CardModel* clickedCard = gameModel.findCard(cardId);
    if (clickedCard == nullptr || clickedCard->getZone() != CZT_PLAYFIELD) {
        outError = u8"\u6240\u9009\u5361\u724C\u4E0D\u662F\u4E3B\u724C\u533A\u53EF\u64CD\u4F5C\u5361\u724C";
        return false;
    }

    const int trayTopCardId = gameModel.getTrayTopCardId();
    CardModel* trayTopCard = gameModel.findCard(trayTopCardId);
    if (trayTopCard == nullptr || trayTopCard->getZone() != CZT_TRAY) {
        outError = u8"\u5F53\u524D\u6CA1\u6709\u53EF\u5339\u914D\u7684\u624B\u724C\u9876\u90E8\u5361\u724C";
        return false;
    }

    if (!GameRuleService::canMatch(*clickedCard, *trayTopCard)) {
        outError = u8"\u5339\u914D\u5931\u8D25\uFF1A\u70B9\u6570\u9700\u8981\u548C\u624B\u724C\u9876\u90E8\u5DEE 1";
        return false;
    }

    outUndo.setActionType(UAT_PLAYFIELD_TO_TRAY);
    outUndo.setMovedCardId(cardId);
    outUndo.setPreviousTrayCardId(trayTopCardId);
    outUndo.setSourceZone(CZT_PLAYFIELD);
    outUndo.setSourcePosition(clickedCard->getCurrentPosition());
    outUndo.setPreviousStackIndex(gameModel.getNextStackIndex());

    clickedCard->setZone(CZT_TRAY);
    clickedCard->setCurrentPosition(trayPosition);
    gameModel.setTrayTopCardId(cardId);
    return true;
}

} // namespace qipai
