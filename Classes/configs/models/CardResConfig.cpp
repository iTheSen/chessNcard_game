#include "configs/models/CardResConfig.h"

namespace qipai {

namespace {

    //±³¾°Í¼Æ¬
const std::string kCardBackgroundPath = "res/cards/card_general.png";

} // namespace

const std::string& CardResConfig::getCardBackgroundPath()
{
    return kCardBackgroundPath;
}

cocos2d::Size CardResConfig::getCardSize()
{
    return cocos2d::Size(182.0f, 282.0f);
}

std::string CardResConfig::getBigNumberPath(CardFaceType face, CardSuitType suit)
{
    const std::string color = isRedSuit(suit) ? "red" : "black";
    return "res/cards/number/big_" + color + "_" + faceToToken(face) + ".png";
}

std::string CardResConfig::getSmallNumberPath(CardFaceType face, CardSuitType suit)
{
    const std::string color = isRedSuit(suit) ? "red" : "black";
    return "res/cards/number/small_" + color + "_" + faceToToken(face) + ".png";
}

std::string CardResConfig::getSuitPath(CardSuitType suit)
{
    switch (suit) {
        case CST_CLUBS:
            return "res/cards/suits/club.png";
        case CST_DIAMONDS:
            return "res/cards/suits/diamond.png";
        case CST_HEARTS:
            return "res/cards/suits/heart.png";
        case CST_SPADES:
            return "res/cards/suits/spade.png";
        default:
            return "res/cards/suits/club.png";
    }
}

std::string CardResConfig::faceToToken(CardFaceType face)
{
    switch (face) {
        case CFT_ACE:
            return "A";
        case CFT_TWO:
            return "2";
        case CFT_THREE:
            return "3";
        case CFT_FOUR:
            return "4";
        case CFT_FIVE:
            return "5";
        case CFT_SIX:
            return "6";
        case CFT_SEVEN:
            return "7";
        case CFT_EIGHT:
            return "8";
        case CFT_NINE:
            return "9";
        case CFT_TEN:
            return "10";
        case CFT_JACK:
            return "J";
        case CFT_QUEEN:
            return "Q";
        case CFT_KING:
            return "K";
        default:
            return "A";
    }
}

bool CardResConfig::isRedSuit(CardSuitType suit)
{
    return suit == CST_DIAMONDS || suit == CST_HEARTS;
}

} // namespace qipai
