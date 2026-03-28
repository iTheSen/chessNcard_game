#ifndef QIPAI_VIEWS_STACK_VIEW_H
#define QIPAI_VIEWS_STACK_VIEW_H

#include <functional>

#include "cocos2d.h"

namespace qipai {

/**
 * @brief 堆牌区与手牌区视图容器。
 *
 * 负责底部区域背景、卡槽提示以及回退按钮。
 */
class StackView : public cocos2d::Node {
public:
    /**
     * @brief 创建堆牌区视图。
     */
    static StackView* create();

    /**
     * @brief 初始化堆牌区视图。
     */
    bool init() override;

    /**
     * @brief 设置撤销按钮点击回调。
     */
    void setUndoCallback(const std::function<void()>& callback);

private:
    /** @brief 回退按钮点击回调。 */
    std::function<void()> _undoCallback;
};

} // namespace qipai

#endif // QIPAI_VIEWS_STACK_VIEW_H
