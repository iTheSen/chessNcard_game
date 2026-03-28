#include "configs/loaders/LevelConfigLoader.h"

#include "cocos2d.h"
#include "json/document.h"

namespace {

bool parseCardArray(
    const rapidjson::Value& arrayValue,
    std::vector<qipai::LevelCardConfig>& outCards,
    std::string* outError)
{
    if (!arrayValue.IsArray()) {
        if (outError != nullptr) {
            *outError = "card list is not an array";
        }
        return false;
    }

    outCards.clear();
    for (rapidjson::SizeType i = 0; i < arrayValue.Size(); ++i) {
        const rapidjson::Value& item = arrayValue[i];
        if (!item.IsObject() || !item.HasMember("CardFace") || !item.HasMember("CardSuit") || !item.HasMember("Position")) {
            if (outError != nullptr) {
                *outError = "card item is missing required fields";
            }
            return false;
        }

        const rapidjson::Value& position = item["Position"];
        if (!position.IsObject() || !position.HasMember("x") || !position.HasMember("y")) {
            if (outError != nullptr) {
                *outError = "position is invalid";
            }
            return false;
        }

        qipai::LevelCardConfig card;
        card.cardFace = item["CardFace"].GetInt();
        card.cardSuit = item["CardSuit"].GetInt();
        card.position = cocos2d::Vec2(
            position["x"].GetFloat(),
            position["y"].GetFloat());
        outCards.push_back(card);
    }

    return true;
}

} // namespace

namespace qipai {

bool LevelConfigLoader::loadLevelConfig(
    const std::string& filePath,
    LevelConfig& outConfig,
    std::string* outError)
{
    const std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
    if (content.empty()) {
        if (outError != nullptr) {
            *outError = "level config file is empty or not found: " + filePath;
        }
        return false;
    }

    rapidjson::Document document;
    document.Parse(content.c_str());
    if (document.HasParseError() || !document.IsObject()) {
        if (outError != nullptr) {
            *outError = "json parse error";
        }
        return false;
    }

    if (!document.HasMember("Playfield") || !document.HasMember("Stack")) {
        if (outError != nullptr) {
            *outError = "missing Playfield or Stack";
        }
        return false;
    }

    std::vector<LevelCardConfig> playFieldCards;
    std::vector<LevelCardConfig> stackCards;
    if (!parseCardArray(document["Playfield"], playFieldCards, outError)) {
        return false;
    }
    if (!parseCardArray(document["Stack"], stackCards, outError)) {
        return false;
    }

    outConfig.setPlayFieldCards(playFieldCards);
    outConfig.setStackCards(stackCards);
    return true;
}

} // namespace qipai
