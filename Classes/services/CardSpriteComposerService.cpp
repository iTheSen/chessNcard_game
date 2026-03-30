#include "services/CardSpriteComposerService.h"

#include "configs/models/CardResConfig.h"

namespace qipai {


    // 开发文档要求 注意函数小于50行
void CardSpriteComposerService::composeFace(cocos2d::Node* cardRoot, CardFaceType face, CardSuitType suit)
{
    if (cardRoot == nullptr) {
        return;
    }

    const cocos2d::Size cardSize = CardResConfig::getCardSize();

    cocos2d::Sprite* bigNumber = cocos2d::Sprite::create(CardResConfig::getBigNumberPath(face, suit));
    if (bigNumber != nullptr) {
        bigNumber->setPosition(cardSize.width * 0.52f, cardSize.height * 0.53f);
        cardRoot->addChild(bigNumber, 2);
    }

    cocos2d::Sprite* smallTop = cocos2d::Sprite::create(CardResConfig::getSmallNumberPath(face, suit));
    if (smallTop != nullptr) {
        smallTop->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
        smallTop->setPosition(15.0f, cardSize.height - 14.0f);
        cardRoot->addChild(smallTop, 2);
    }

    cocos2d::Sprite* suitTop = cocos2d::Sprite::create(CardResConfig::getSuitPath(suit));
    if (suitTop != nullptr) {
        suitTop->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
        suitTop->setScale(0.74f);
        suitTop->setPosition(18.0f, cardSize.height - 58.0f);
        cardRoot->addChild(suitTop, 2);
    }

    cocos2d::Sprite* smallBottom = cocos2d::Sprite::create(CardResConfig::getSmallNumberPath(face, suit));
    if (smallBottom != nullptr) {
        smallBottom->setAnchorPoint(cocos2d::Vec2(1.0f, 0.0f));
        smallBottom->setFlippedX(true);
        smallBottom->setFlippedY(true);
        smallBottom->setPosition(cardSize.width - 15.0f, 14.0f);
        cardRoot->addChild(smallBottom, 2);
    }

    cocos2d::Sprite* suitBottom = cocos2d::Sprite::create(CardResConfig::getSuitPath(suit));
    if (suitBottom != nullptr) {
        suitBottom->setAnchorPoint(cocos2d::Vec2(1.0f, 0.0f));
        suitBottom->setScale(0.74f);
        suitBottom->setFlippedX(true);
        suitBottom->setFlippedY(true);
        suitBottom->setPosition(cardSize.width - 18.0f, 58.0f);
        cardRoot->addChild(suitBottom, 2);
    }
}

} // namespace qipai
