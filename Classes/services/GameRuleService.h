#ifndef QIPAI_SERVICES_GAME_RULE_SERVICE_H
#define QIPAI_SERVICES_GAME_RULE_SERVICE_H

#include "models/CardModel.h"

namespace qipai {

/**
 * @brief 游戏规则服务。
 *
 * 提供无状态匹配判断逻辑。
 */
class GameRuleService {
public:
    /**
     * @brief 判断两张牌是否满足点数差 1 的匹配规则。
     */
    static bool canMatch(const CardModel& sourceCard, const CardModel& trayCard);

    /**
     * @brief 判断两个点数是否满足点数差 1。
     */
    static bool canMatchFace(CardFaceType sourceFace, CardFaceType trayFace);
};

} // namespace qipai

#endif // QIPAI_SERVICES_GAME_RULE_SERVICE_H
