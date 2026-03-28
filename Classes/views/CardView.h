#ifndef QIPAI_VIEWS_CARD_VIEW_H
#define QIPAI_VIEWS_CARD_VIEW_H

#include <functional>

#include "cocos2d.h"
#include "models/CardModel.h"

namespace qipai {

/**
 * @brief 单张卡牌视图组件。
 *
 * 负责卡牌绘制、点击事件与移动动画。
 */
class CardView : public cocos2d::Node {
public:
    /**
     * @brief 创建卡牌视图。
     */
    static CardView* create(const CardModel& cardModel);

    /**
     * @brief 初始化卡牌视图。
     */
    bool initWithCard(const CardModel& cardModel);

    /**
     * @brief 设置点击回调。
     */
    void setOnClickCallback(const std::function<void(int)>& callback);

    /**
     * @brief 设置是否可交互。
     */
    void setInteractionEnabled(bool enabled);

    /**
     * @brief 获取是否可交互。
     */
    bool isInteractionEnabled() const;

    /**
     * @brief 获取卡牌 ID。
     */
    int getCardId() const;

    /**
     * @brief 播放移动动画。
     */
    void moveTo(const cocos2d::Vec2& targetPosition, float duration, const std::function<void()>& onComplete);

private:
    /**
     * @brief 注册触摸事件监听。
     */
    void registerTouchListener();

    /** @brief 卡牌 ID。 */
    int _cardId = -1;

    /** @brief 是否允许触摸交互。 */
    bool _interactionEnabled = true;

    /** @brief 点击回调函数。 */
    std::function<void(int)> _onClickCallback;

    /** @brief 触摸监听器。 */
    cocos2d::EventListenerTouchOneByOne* _touchListener = nullptr;
};

} // namespace qipai

#endif // QIPAI_VIEWS_CARD_VIEW_H
