#ifndef QIPAI_CONFIGS_MODELS_LEVEL_CONFIG_H
#define QIPAI_CONFIGS_MODELS_LEVEL_CONFIG_H

#include <vector>
#include "cocos2d.h"

namespace qipai {

/**
 * @brief 单张卡牌的静态配置数据。
 */
struct LevelCardConfig {
    /** @brief 点数配置值，对应 CardFaceType 的整数值。 */
    int cardFace = -1;//NONE

    /** @brief 花色配置值，对应 CardSuitType 的整数值。 */
    int cardSuit = -1;//NONE

    /** @brief 配置中的卡牌坐标。 */
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
};

/**
 * @brief 关卡静态配置模型。
 *
 * 包含主牌区和堆牌区的所有卡牌初始数据。
 */
class LevelConfig {
public:
    /**
     * @brief 获取主牌区静态卡牌列表。
     */
    const std::vector<LevelCardConfig>& getPlayFieldCards() const;

    /**
     * @brief 获取堆牌区静态卡牌列表。
     */
    const std::vector<LevelCardConfig>& getStackCards() const;

    /**
     * @brief 设置主牌区静态卡牌列表。
     */
    void setPlayFieldCards(const std::vector<LevelCardConfig>& cards);

    /**
     * @brief 设置堆牌区静态卡牌列表。
     */
    void setStackCards(const std::vector<LevelCardConfig>& cards);

private:
    /** @brief 主牌区卡牌配置集合。 */
    std::vector<LevelCardConfig> _playFieldCards;

    /** @brief 堆牌区卡牌配置集合。 */
    std::vector<LevelCardConfig> _stackCards;
};

} // namespace qipai

#endif // QIPAI_CONFIGS_MODELS_LEVEL_CONFIG_H
