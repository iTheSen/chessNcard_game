#include "controllers/StackController.h"

namespace qipai {

bool StackController::handleStackCardClick(
    GameModel& gameModel,
    const cocos2d::Vec2& stackPosition,
    const cocos2d::Vec2& trayPosition,
    UndoModel& outUndo,
    std::string& outError) const
{
    if (!gameModel.canDrawFromStack()) {
        outError = u8"\u5907\u7528\u724C\u5DF2\u8017\u5C3D";
        return false;
    }

    const int nextStackCardId = gameModel.peekNextStackCardId();
    CardModel* card = gameModel.findCard(nextStackCardId);
    if (card == nullptr || card->getZone() != CZT_STACK) {
        outError = u8"\u5F53\u524D\u5907\u7528\u724C\u72B6\u6001\u5F02\u5E38";
        return false;
    }

    outUndo.setActionType(UAT_STACK_TO_TRAY);
    outUndo.setMovedCardId(nextStackCardId);
    outUndo.setPreviousTrayCardId(gameModel.getTrayTopCardId());
    outUndo.setSourceZone(CZT_STACK);
    outUndo.setSourcePosition(stackPosition);
    outUndo.setPreviousStackIndex(gameModel.getNextStackIndex());

    card->setZone(CZT_TRAY);
    card->setCurrentPosition(trayPosition);
    gameModel.setNextStackIndex(gameModel.getNextStackIndex() + 1);
    gameModel.setTrayTopCardId(nextStackCardId);
    return true;
}

} // namespace qipai
