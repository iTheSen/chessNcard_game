#include "services/GameModelFromLevelGenerator.h"

#include "utils/LayoutConstants.h"

namespace qipai {

namespace {

CardModel buildCardModel(int cardId, const LevelCardConfig& config, CardZoneType zone)
{
    cocos2d::Vec2 initialPosition = config.position;
    if (zone == CZT_PLAYFIELD) {
        // Level config positions are defined in the playfield local space.
        initialPosition.y += layout::kStackHeight;
    }

    return CardModel(
        cardId,
        static_cast<CardFaceType>(config.cardFace),
        static_cast<CardSuitType>(config.cardSuit),
        zone,
        initialPosition);
}

} // namespace

GameModel GameModelFromLevelGenerator::generateGameModel(const LevelConfig& levelConfig)
{
    GameModel gameModel;
    int nextCardId = 1;

    const std::vector<LevelCardConfig>& playFieldCards = levelConfig.getPlayFieldCards();
    for (const LevelCardConfig& cardConfig : playFieldCards) {
        gameModel.addPlayFieldCard(buildCardModel(nextCardId, cardConfig, CZT_PLAYFIELD));
        ++nextCardId;
    }

    const std::vector<LevelCardConfig>& stackCards = levelConfig.getStackCards();
    for (size_t i = 0; i < stackCards.size(); ++i) {
        CardZoneType zone = CZT_STACK;
        if (i == 0) {
            zone = CZT_TRAY;
        }

        gameModel.addStackCard(buildCardModel(nextCardId, stackCards[i], zone));
        ++nextCardId;
    }

    const std::vector<int>& stackCardIds = gameModel.getStackCardIds();
    if (stackCardIds.empty()) {
        gameModel.setTrayTopCardId(-1);
        gameModel.setNextStackIndex(0);
        return gameModel;
    }

    gameModel.setTrayTopCardId(stackCardIds[0]);
    gameModel.setNextStackIndex(1);
    return gameModel;
}

} // namespace qipai
