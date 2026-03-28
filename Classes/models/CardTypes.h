#ifndef QIPAI_MODELS_CARD_TYPES_H
#define QIPAI_MODELS_CARD_TYPES_H

namespace qipai {

/**
 * @brief 卡牌花色枚举。
 */
enum CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,
    CST_DIAMONDS,
    CST_HEARTS,
    CST_SPADES,
    CST_NUM_CARD_SUIT_TYPES
};

/**
 * @brief 卡牌点数枚举。
 */
enum CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

/**
 * @brief 卡牌当前所在区域类型。
 */
enum CardZoneType {
    CZT_NONE = -1,
    CZT_PLAYFIELD,
    CZT_STACK,
    CZT_TRAY
};

} // namespace qipai

#endif // QIPAI_MODELS_CARD_TYPES_H
