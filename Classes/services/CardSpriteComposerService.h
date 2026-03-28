#ifndef QIPAI_SERVICES_CARD_SPRITE_COMPOSER_SERVICE_H
#define QIPAI_SERVICES_CARD_SPRITE_COMPOSER_SERVICE_H

#include "cocos2d.h"
#include "models/CardTypes.h"

namespace qipai {

/**
 * @brief 卡牌牌面拼装服务。
 *
 * 根据点数和花色向节点中添加牌面元素。
 */
class CardSpriteComposerService {
public:
    /**
     * @brief 拼装完整牌面元素。
     * @param cardRoot 卡牌根节点。
     * @param face 点数。
     * @param suit 花色。
     */
    static void composeFace(cocos2d::Node* cardRoot, CardFaceType face, CardSuitType suit);
};

} // namespace qipai

#endif // QIPAI_SERVICES_CARD_SPRITE_COMPOSER_SERVICE_H
