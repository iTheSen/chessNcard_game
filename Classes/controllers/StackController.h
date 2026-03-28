#ifndef QIPAI_CONTROLLERS_STACK_CONTROLLER_H
#define QIPAI_CONTROLLERS_STACK_CONTROLLER_H

#include <string>

#include "models/GameModel.h"
#include "models/UndoModel.h"

namespace qipai {

/**
 * @brief 堆牌区控制器。
 *
 * 负责点击备用牌后替换手牌顶部的逻辑。
 */
class StackController {
public:
    /**
     * @brief 处理备用牌点击替换逻辑。
     * @param gameModel 游戏模型。
     * @param stackPosition 备用牌区域坐标。
     * @param trayPosition 手牌顶部坐标。
     * @param outUndo 输出回退记录。
     * @param outError 输出错误信息。
     * @return 是否替换成功。
     */
    bool handleStackCardClick(
        GameModel& gameModel,
        const cocos2d::Vec2& stackPosition,
        const cocos2d::Vec2& trayPosition,
        UndoModel& outUndo,
        std::string& outError) const;
};

} // namespace qipai

#endif // QIPAI_CONTROLLERS_STACK_CONTROLLER_H
