#ifndef QIPAI_SERVICES_GAME_MODEL_FROM_LEVEL_GENERATOR_H
#define QIPAI_SERVICES_GAME_MODEL_FROM_LEVEL_GENERATOR_H

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

namespace qipai {

/**
 * @brief 运行态模型生成服务。
 *
 * 将静态关卡配置转换为运行态 GameModel。
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief 根据关卡配置生成运行态模型。
     */
    static GameModel generateGameModel(const LevelConfig& levelConfig);
};

} // namespace qipai

#endif // QIPAI_SERVICES_GAME_MODEL_FROM_LEVEL_GENERATOR_H
