#ifndef QIPAI_VIEWS_PLAY_FIELD_VIEW_H
#define QIPAI_VIEWS_PLAY_FIELD_VIEW_H

#include "cocos2d.h"

namespace qipai {

/**
 * @brief 主牌区视图容器。
 *
 * 负责主牌区背景、边界与提示信息展示。
 */
class PlayFieldView : public cocos2d::Node {
public:
    /**
     * @brief 创建主牌区视图。
     */
    static PlayFieldView* create();

    /**
     * @brief 初始化主牌区视图。
     */
    bool init() override;
};

} // namespace qipai

#endif // QIPAI_VIEWS_PLAY_FIELD_VIEW_H
