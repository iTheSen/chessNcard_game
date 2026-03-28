#include "models/UndoModel.h"

namespace qipai {

UndoActionType UndoModel::getActionType() const
{
    return _actionType;
}

void UndoModel::setActionType(UndoActionType actionType)
{
    _actionType = actionType;
}

int UndoModel::getMovedCardId() const
{
    return _movedCardId;
}

void UndoModel::setMovedCardId(int cardId)
{
    _movedCardId = cardId;
}

int UndoModel::getPreviousTrayCardId() const
{
    return _previousTrayCardId;
}

void UndoModel::setPreviousTrayCardId(int cardId)
{
    _previousTrayCardId = cardId;
}

CardZoneType UndoModel::getSourceZone() const
{
    return _sourceZone;
}

void UndoModel::setSourceZone(CardZoneType zone)
{
    _sourceZone = zone;
}

const cocos2d::Vec2& UndoModel::getSourcePosition() const
{
    return _sourcePosition;
}

void UndoModel::setSourcePosition(const cocos2d::Vec2& position)
{
    _sourcePosition = position;
}

int UndoModel::getPreviousStackIndex() const
{
    return _previousStackIndex;
}

void UndoModel::setPreviousStackIndex(int index)
{
    _previousStackIndex = index;
}

rapidjson::Value UndoModel::toJson(rapidjson::Document::AllocatorType& allocator) const
{
    rapidjson::Value value(rapidjson::kObjectType);
    value.AddMember("ActionType", static_cast<int>(_actionType), allocator);
    value.AddMember("MovedCardId", _movedCardId, allocator);
    value.AddMember("PreviousTrayCardId", _previousTrayCardId, allocator);
    value.AddMember("SourceZone", static_cast<int>(_sourceZone), allocator);
    value.AddMember("PreviousStackIndex", _previousStackIndex, allocator);

    rapidjson::Value sourcePos(rapidjson::kObjectType);
    sourcePos.AddMember("x", _sourcePosition.x, allocator);
    sourcePos.AddMember("y", _sourcePosition.y, allocator);
    value.AddMember("SourcePosition", sourcePos, allocator);
    return value;
}

UndoModel UndoModel::fromJson(const rapidjson::Value& value)
{
    UndoModel model;
    if (!value.IsObject()) {
        return model;
    }

    model._actionType = static_cast<UndoActionType>(value["ActionType"].GetInt());
    model._movedCardId = value["MovedCardId"].GetInt();
    model._previousTrayCardId = value["PreviousTrayCardId"].GetInt();
    model._sourceZone = static_cast<CardZoneType>(value["SourceZone"].GetInt());
    model._previousStackIndex = value["PreviousStackIndex"].GetInt();

    const rapidjson::Value& sourcePos = value["SourcePosition"];
    model._sourcePosition = cocos2d::Vec2(sourcePos["x"].GetFloat(), sourcePos["y"].GetFloat());
    return model;
}

} // namespace qipai
