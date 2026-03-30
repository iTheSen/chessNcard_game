#include "models/GameModel.h"

#include <algorithm>

namespace qipai {

void GameModel::addPlayFieldCard(const CardModel& card)
{
    _cards[card.getCardId()] = card;
    _playFieldCardIds.push_back(card.getCardId());
}

void GameModel::addStackCard(const CardModel& card)
{
    _cards[card.getCardId()] = card;
    _stackCardIds.push_back(card.getCardId());
}

CardModel* GameModel::findCard(int cardId)
{
    auto iter = _cards.find(cardId);
    if (iter == _cards.end()) {
        return nullptr;
    }
    return &iter->second;
}

const CardModel* GameModel::findCard(int cardId) const
{
    auto iter = _cards.find(cardId);
    if (iter == _cards.end()) {
        return nullptr;
    }
    return &iter->second;
}

const std::vector<int>& GameModel::getPlayFieldCardIds() const
{
    return _playFieldCardIds;
}

const std::vector<int>& GameModel::getStackCardIds() const
{
    return _stackCardIds;
}

std::vector<int> GameModel::getAllCardIds() const
{
    std::vector<int> ids;
    ids.reserve(_cards.size());
    for (const auto& pair : _cards) {
        ids.push_back(pair.first);
    }
    std::sort(ids.begin(), ids.end());
    return ids;
}

bool GameModel::canDrawFromStack() const
{
    return _nextStackIndex >= 0 && _nextStackIndex < static_cast<int>(_stackCardIds.size());
}

int GameModel::peekNextStackCardId() const
{
    if (!canDrawFromStack()) {
        return -1;
    }
    return _stackCardIds[_nextStackIndex];
}

int GameModel::getTrayTopCardId() const
{
    return _trayTopCardId;
}

void GameModel::setTrayTopCardId(int cardId)
{
    _trayTopCardId = cardId;
}

int GameModel::getNextStackIndex() const
{
    return _nextStackIndex;
}

void GameModel::setNextStackIndex(int index)
{
    _nextStackIndex = index;
}

// 目前没有调用栈
rapidjson::Value GameModel::toJson(rapidjson::Document::AllocatorType& allocator) const
{
    rapidjson::Value root(rapidjson::kObjectType);

    rapidjson::Value cards(rapidjson::kArrayType);
    for (int cardId : getAllCardIds()) {
        const CardModel* card = findCard(cardId);
        if (card == nullptr) {
            continue;
        }
        cards.PushBack(card->toJson(allocator), allocator);
    }
    root.AddMember("Cards", cards, allocator);

    rapidjson::Value playFieldIds(rapidjson::kArrayType);
    for (int cardId : _playFieldCardIds) {
        playFieldIds.PushBack(cardId, allocator);
    }
    root.AddMember("PlayFieldCardIds", playFieldIds, allocator);

    rapidjson::Value stackIds(rapidjson::kArrayType);
    for (int cardId : _stackCardIds) {
        stackIds.PushBack(cardId, allocator);
    }
    root.AddMember("StackCardIds", stackIds, allocator);

    root.AddMember("TrayTopCardId", _trayTopCardId, allocator);
    root.AddMember("NextStackIndex", _nextStackIndex, allocator);
    return root;
}

GameModel GameModel::fromJson(const rapidjson::Value& value)
{
    GameModel model;
    if (!value.IsObject()) {
        return model;
    }

    if (value.HasMember("Cards") && value["Cards"].IsArray()) {
        const rapidjson::Value& cards = value["Cards"];
        for (rapidjson::SizeType i = 0; i < cards.Size(); ++i) {
            CardModel card = CardModel::fromJson(cards[i]);
            model._cards[card.getCardId()] = card;
        }
    }

    if (value.HasMember("PlayFieldCardIds") && value["PlayFieldCardIds"].IsArray()) {
        const rapidjson::Value& playFieldIds = value["PlayFieldCardIds"];
        for (rapidjson::SizeType i = 0; i < playFieldIds.Size(); ++i) {
            model._playFieldCardIds.push_back(playFieldIds[i].GetInt());
        }
    }

    if (value.HasMember("StackCardIds") && value["StackCardIds"].IsArray()) {
        const rapidjson::Value& stackIds = value["StackCardIds"];
        for (rapidjson::SizeType i = 0; i < stackIds.Size(); ++i) {
            model._stackCardIds.push_back(stackIds[i].GetInt());
        }
    }

    if (value.HasMember("TrayTopCardId")) {
        model._trayTopCardId = value["TrayTopCardId"].GetInt();
    }
    if (value.HasMember("NextStackIndex")) {
        model._nextStackIndex = value["NextStackIndex"].GetInt();
    }

    return model;
}

} // namespace qipai
