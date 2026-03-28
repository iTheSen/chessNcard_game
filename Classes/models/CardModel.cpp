#include "models/CardModel.h"

namespace qipai {

CardModel::CardModel(
    int cardId,
    CardFaceType face,
    CardSuitType suit,
    CardZoneType zone,
    const cocos2d::Vec2& position)
    : _cardId(cardId)
    , _face(face)
    , _suit(suit)
    , _zone(zone)
    , _originalPosition(position)
    , _currentPosition(position)
{
}

int CardModel::getCardId() const
{
    return _cardId;
}

CardFaceType CardModel::getFace() const
{
    return _face;
}

CardSuitType CardModel::getSuit() const
{
    return _suit;
}

CardZoneType CardModel::getZone() const
{
    return _zone;
}

void CardModel::setZone(CardZoneType zone)
{
    _zone = zone;
}

const cocos2d::Vec2& CardModel::getCurrentPosition() const
{
    return _currentPosition;
}

void CardModel::setCurrentPosition(const cocos2d::Vec2& position)
{
    _currentPosition = position;
}

const cocos2d::Vec2& CardModel::getOriginalPosition() const
{
    return _originalPosition;
}

void CardModel::setOriginalPosition(const cocos2d::Vec2& position)
{
    _originalPosition = position;
}

rapidjson::Value CardModel::toJson(rapidjson::Document::AllocatorType& allocator) const
{
    rapidjson::Value value(rapidjson::kObjectType);
    value.AddMember("CardId", _cardId, allocator);
    value.AddMember("Face", static_cast<int>(_face), allocator);
    value.AddMember("Suit", static_cast<int>(_suit), allocator);
    value.AddMember("Zone", static_cast<int>(_zone), allocator);

    rapidjson::Value origin(rapidjson::kObjectType);
    origin.AddMember("x", _originalPosition.x, allocator);
    origin.AddMember("y", _originalPosition.y, allocator);
    value.AddMember("OriginalPosition", origin, allocator);

    rapidjson::Value current(rapidjson::kObjectType);
    current.AddMember("x", _currentPosition.x, allocator);
    current.AddMember("y", _currentPosition.y, allocator);
    value.AddMember("CurrentPosition", current, allocator);
    return value;
}

CardModel CardModel::fromJson(const rapidjson::Value& value)
{
    CardModel card;
    if (!value.IsObject()) {
        return card;
    }

    const rapidjson::Value& origin = value["OriginalPosition"];
    const rapidjson::Value& current = value["CurrentPosition"];

    card = CardModel(
        value["CardId"].GetInt(),
        static_cast<CardFaceType>(value["Face"].GetInt()),
        static_cast<CardSuitType>(value["Suit"].GetInt()),
        static_cast<CardZoneType>(value["Zone"].GetInt()),
        cocos2d::Vec2(origin["x"].GetFloat(), origin["y"].GetFloat()));
    card.setCurrentPosition(cocos2d::Vec2(current["x"].GetFloat(), current["y"].GetFloat()));
    return card;
}

} // namespace qipai
