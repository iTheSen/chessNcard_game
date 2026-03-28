#ifndef QIPAI_CONFIGS_MODELS_CARD_RES_CONFIG_H
#define QIPAI_CONFIGS_MODELS_CARD_RES_CONFIG_H

#include <string>
#include "cocos2d.h"
#include "models/CardTypes.h"

namespace qipai {

/**
 * @brief 卡牌资源路径配置。
 *
 * 提供牌面绘制所需的所有资源路径计算逻辑。
 */
class CardResConfig {
public:
    /**
     * @brief 获取卡牌底图路径。
     */
    static const std::string& getCardBackgroundPath();

    /**
     * @brief 获取卡牌底图尺寸。
     */
    static cocos2d::Size getCardSize();

    /**
     * @brief 获取大号点数字体图路径。
     */
    static std::string getBigNumberPath(CardFaceType face, CardSuitType suit);

    /**
     * @brief 获取小号点数字体图路径。
     */
    static std::string getSmallNumberPath(CardFaceType face, CardSuitType suit);

    /**
     * @brief 获取花色图路径。
     */
    static std::string getSuitPath(CardSuitType suit);

private:
    /**
     * @brief 将点数转成资源名后缀。
     */
    static std::string faceToToken(CardFaceType face);

    /**
     * @brief 判断花色是否为红色。
     */
    static bool isRedSuit(CardSuitType suit);
};

} // namespace qipai

#endif // QIPAI_CONFIGS_MODELS_CARD_RES_CONFIG_H
