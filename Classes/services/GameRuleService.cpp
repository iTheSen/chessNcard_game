#include "services/GameRuleService.h"

#include <cmath>

namespace qipai {

bool GameRuleService::canMatch(const CardModel& sourceCard, const CardModel& trayCard)
{
    return canMatchFace(sourceCard.getFace(), trayCard.getFace());
}

bool GameRuleService::canMatchFace(CardFaceType sourceFace, CardFaceType trayFace)
{
    if (sourceFace == CFT_NONE || trayFace == CFT_NONE) {
        return false;
    }

    const int sourceValue = static_cast<int>(sourceFace);
    const int trayValue = static_cast<int>(trayFace);
    return std::abs(sourceValue - trayValue) == 1;
}

} // namespace qipai
