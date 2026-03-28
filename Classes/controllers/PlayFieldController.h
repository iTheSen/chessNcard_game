#ifndef QIPAI_CONTROLLERS_PLAY_FIELD_CONTROLLER_H
#define QIPAI_CONTROLLERS_PLAY_FIELD_CONTROLLER_H

#include <string>

#include "models/GameModel.h"
#include "models/UndoModel.h"

namespace qipai {

/**
 * @brief 主牌区控制器。
 *
 * 负责主牌区卡牌点击后的匹配规则校验与模型更新。
 */
class PlayFieldController {
public:
    /**
     * @brief 处理主牌区卡牌点击。
     * @param gameModel 游戏模型。
     * @param cardId 被点击卡牌 ID。
     * @param trayPosition 手牌顶部坐标。
     * @param outUndo 输出回退记录。
     * @param outError 输出错误信息。
     * @return 是否匹配成功并完成替换。
     */
    bool handleCardClick(
        GameModel& gameModel,
        int cardId,
        const cocos2d::Vec2& trayPosition,
        UndoModel& outUndo,
        std::string& outError) const;
};

} // namespace qipai

#endif // QIPAI_CONTROLLERS_PLAY_FIELD_CONTROLLER_H
