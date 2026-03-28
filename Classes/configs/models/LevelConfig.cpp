#include "configs/models/LevelConfig.h"

namespace qipai {

const std::vector<LevelCardConfig>& LevelConfig::getPlayFieldCards() const
{
    return _playFieldCards;
}

const std::vector<LevelCardConfig>& LevelConfig::getStackCards() const
{
    return _stackCards;
}

void LevelConfig::setPlayFieldCards(const std::vector<LevelCardConfig>& cards)
{
    _playFieldCards = cards;
}

void LevelConfig::setStackCards(const std::vector<LevelCardConfig>& cards)
{
    _stackCards = cards;
}

} // namespace qipai
