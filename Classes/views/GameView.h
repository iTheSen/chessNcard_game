#ifndef QIPAI_VIEWS_GAME_VIEW_H
#define QIPAI_VIEWS_GAME_VIEW_H

#include <functional>
#include <unordered_map>

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/CardView.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"

namespace qipai {

/**
 * @brief 游戏总视图。
 *
 * 组合主牌区和堆牌区，并统一管理全部卡牌视图节点。
 */
class GameView : public cocos2d::Layer {
public:
    /**
     * @brief 创建游戏总视图。
     */
    static GameView* create();

    /**
     * @brief 初始化游戏总视图。
     */
    bool init() override;

    /**
     * @brief 设置卡牌点击回调。
     */
    void setOnCardClickCallback(const std::function<void(int)>& callback);

    /**
     * @brief 设置回退按钮点击回调。
     */
    void setOnUndoClickCallback(const std::function<void()>& callback);

    /**
     * @brief 根据模型初始化全部卡牌视图。
     */
    void buildCards(const GameModel& gameModel);

    /**
     * @brief 获取指定卡牌视图。
     */
    CardView* getCardView(int cardId) const;

    /**
     * @brief 设置卡牌可见性。
     */
    void setCardVisible(int cardId, bool visible);

    /**
     * @brief 设置卡牌交互开关。
     */
    void setCardInteraction(int cardId, bool enabled);

    /**
     * @brief 设置卡牌坐标。
     */
    void setCardPosition(int cardId, const cocos2d::Vec2& position);

    /**
     * @brief 设置卡牌层级。
     */
    void setCardZOrder(int cardId, int zOrder);

    /**
     * @brief 播放卡牌移动动画。
     */
    void moveCard(int cardId, const cocos2d::Vec2& targetPosition, float duration, const std::function<void()>& onComplete);

    /**
     * @brief 获取手牌顶部坐标。
     */
    cocos2d::Vec2 getTrayCardPosition() const;

    /**
     * @brief 获取备用牌坐标。
     */
    cocos2d::Vec2 getStackCardPosition() const;

    /**
     * @brief 设置状态提示文本。
     */
    void setStatusText(const std::string& text);

private:
    /**
     * @brief 清理已创建的卡牌节点。
     */
    void clearCards();

    /** @brief 主牌区视图。 */
    PlayFieldView* _playFieldView = nullptr;

    /** @brief 堆牌区视图。 */
    StackView* _stackView = nullptr;

    /** @brief 状态提示文本。 */
    cocos2d::Label* _statusLabel = nullptr;

    /** @brief 卡牌点击回调。 */
    std::function<void(int)> _onCardClickCallback;

    /** @brief 回退按钮点击回调。 */
    std::function<void()> _onUndoClickCallback;

    /** @brief 卡牌视图字典。 */
    std::unordered_map<int, CardView*> _cardViews;
};

} // namespace qipai

#endif // QIPAI_VIEWS_GAME_VIEW_H
