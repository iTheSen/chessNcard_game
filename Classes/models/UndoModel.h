#ifndef QIPAI_MODELS_UNDO_MODEL_H
#define QIPAI_MODELS_UNDO_MODEL_H

#include "cocos2d.h"
#include "json/document.h"
#include "models/CardTypes.h"

namespace qipai {

/**
 * @brief 回退动作类型。
 */
enum UndoActionType {
    UAT_NONE = 0,
    UAT_STACK_TO_TRAY,
    UAT_PLAYFIELD_TO_TRAY
};

/**
 * @brief 单步回退记录模型。
 *
 * 用于描述一次卡牌移动在回退时所需恢复的数据。
 */
class UndoModel {
public:
    /** @brief 获取动作类型。 */
    UndoActionType getActionType() const;

    /** @brief 设置动作类型。 */
    void setActionType(UndoActionType actionType);

    /** @brief 获取被移动的卡牌 ID。 */
    int getMovedCardId() const;

    /** @brief 设置被移动的卡牌 ID。 */
    void setMovedCardId(int cardId);

    /** @brief 获取移动前的顶部手牌 ID。 */
    int getPreviousTrayCardId() const;

    /** @brief 设置移动前的顶部手牌 ID。 */
    void setPreviousTrayCardId(int cardId);

    /** @brief 获取被移动卡牌的来源区域。 */
    CardZoneType getSourceZone() const;

    /** @brief 设置被移动卡牌的来源区域。 */
    void setSourceZone(CardZoneType zone);

    /** @brief 获取被移动卡牌的来源坐标。 */
    const cocos2d::Vec2& getSourcePosition() const;

    /** @brief 设置被移动卡牌的来源坐标。 */
    void setSourcePosition(const cocos2d::Vec2& position);

    /** @brief 获取动作执行前的堆牌索引。 */
    int getPreviousStackIndex() const;

    /** @brief 设置动作执行前的堆牌索引。 */
    void setPreviousStackIndex(int index);

    /**
     * @brief 序列化为 JSON 对象。
     */
    rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief 从 JSON 对象反序列化。
     */
    static UndoModel fromJson(const rapidjson::Value& value);

private:
    /** @brief 回退动作类型。 */
    UndoActionType _actionType = UAT_NONE;

    /** @brief 被移动卡牌 ID。 */
    int _movedCardId = -1;

    /** @brief 移动前顶部手牌 ID。 */
    int _previousTrayCardId = -1;

    /** @brief 卡牌来源区域。 */
    CardZoneType _sourceZone = CZT_NONE;

    /** @brief 卡牌来源坐标。 */
    cocos2d::Vec2 _sourcePosition = cocos2d::Vec2::ZERO;

    /** @brief 操作前堆牌索引。 */
    int _previousStackIndex = 0;
};

} // namespace qipai

#endif // QIPAI_MODELS_UNDO_MODEL_H
