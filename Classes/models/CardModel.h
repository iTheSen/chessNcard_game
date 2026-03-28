#ifndef QIPAI_MODELS_CARD_MODEL_H
#define QIPAI_MODELS_CARD_MODEL_H

#include "cocos2d.h"
#include "json/document.h"
#include "models/CardTypes.h"

namespace qipai {

/**
 * @brief 运行时卡牌数据模型。
 */
class CardModel {
public:
    /**
     * @brief 默认构造函数。
     */
    CardModel() = default;

    /**
     * @brief 带参数构造函数。
     */
    CardModel(
        int cardId,
        CardFaceType face,
        CardSuitType suit,
        CardZoneType zone,
        const cocos2d::Vec2& position);

    /** @brief 获取卡牌 ID。 */
    int getCardId() const;

    /** @brief 获取点数。 */
    CardFaceType getFace() const;

    /** @brief 获取花色。 */
    CardSuitType getSuit() const;

    /** @brief 获取所在区域。 */
    CardZoneType getZone() const;

    /** @brief 设置所在区域。 */
    void setZone(CardZoneType zone);

    /** @brief 获取当前坐标。 */
    const cocos2d::Vec2& getCurrentPosition() const;

    /** @brief 设置当前坐标。 */
    void setCurrentPosition(const cocos2d::Vec2& position);

    /** @brief 获取初始坐标。 */
    const cocos2d::Vec2& getOriginalPosition() const;

    /** @brief 设置初始坐标。 */
    void setOriginalPosition(const cocos2d::Vec2& position);

    /**
     * @brief 序列化为 JSON 对象。
     */
    rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief 从 JSON 对象反序列化。
     */
    static CardModel fromJson(const rapidjson::Value& value);

private:
    /** @brief 卡牌唯一 ID。 */
    int _cardId = -1;

    /** @brief 卡牌点数。 */
    CardFaceType _face = CFT_NONE;

    /** @brief 卡牌花色。 */
    CardSuitType _suit = CST_NONE;

    /** @brief 卡牌所属区域。 */
    CardZoneType _zone = CZT_NONE;

    /** @brief 卡牌初始坐标。 */
    cocos2d::Vec2 _originalPosition = cocos2d::Vec2::ZERO;

    /** @brief 卡牌当前坐标。 */
    cocos2d::Vec2 _currentPosition = cocos2d::Vec2::ZERO;
};

} // namespace qipai

#endif // QIPAI_MODELS_CARD_MODEL_H
