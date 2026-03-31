#include "views/CardView.h"

#include <new>

#include "configs/models/CardResConfig.h"
#include "services/CardSpriteComposerService.h"

namespace qipai {


// 
CardView* CardView::create(const CardModel& cardModel)
{
    CardView* cardView = new (std::nothrow) CardView();
    if (cardView == nullptr) {
        return nullptr;
    }

    if (!cardView->initWithCard(cardModel)) {
        delete cardView;
        return nullptr;
    }

    // 调父类Ref的autorelease把cardView放到释放池里
    // 继承链 CardView->Node->Ref
    cardView->autorelease();
    return cardView;
}

// 把牌的样子构建出来
bool CardView::initWithCard(const CardModel& cardModel)
{
    if (!Node::init()) {
        return false;
    }

    _cardId = cardModel.getCardId();
    setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));

    // 设置背景图片 ${resource}/res/cards/card_general.png
    // 还涉及到渲染render方式
    cocos2d::Sprite* background = cocos2d::Sprite::create(CardResConfig::getCardBackgroundPath());
    if (background == nullptr) {
        return false;
    }

    const cocos2d::Size cardSize = CardResConfig::getCardSize();
    setContentSize(cardSize);

    // 卡牌的背景阴影部分代码。
    cocos2d::DrawNode* shadow = cocos2d::DrawNode::create();
    shadow->drawSolidRect(
        cocos2d::Vec2(4.0f, -5.0f),
        cocos2d::Vec2(cardSize.width + 5.0f, cardSize.height - 3.0f),
        cocos2d::Color4F(0.0f, 0.0f, 0.0f, 0.12f));
    addChild(shadow, 0);
    //

    background->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    background->setPosition(cocos2d::Vec2::ZERO);
    addChild(background, 1);

    CardSpriteComposerService::composeFace(this, cardModel.getFace(), cardModel.getSuit());
    setPosition(cardModel.getCurrentPosition());

    registerTouchListener();
    return true;
}

void CardView::setOnClickCallback(const std::function<void(int)>& callback)
{
    _onClickCallback = callback;
}

void CardView::setInteractionEnabled(bool enabled)
{
    _interactionEnabled = enabled;
}

bool CardView::isInteractionEnabled() const
{
    return _interactionEnabled;
}

int CardView::getCardId() const
{
    return _cardId;
}

void CardView::moveTo(const cocos2d::Vec2& targetPosition, float duration, const std::function<void()>& onComplete)
{
    stopAllActions();
    cocos2d::FiniteTimeAction* move = cocos2d::MoveTo::create(duration, targetPosition);
    cocos2d::FiniteTimeAction* callback = cocos2d::CallFunc::create([onComplete]() {
        if (onComplete != nullptr) {
            onComplete();
        }
    });
    runAction(cocos2d::Sequence::create(move, callback, nullptr));
}

void CardView::registerTouchListener()
{
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);

    _touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        CC_UNUSED_PARAM(event);
        if (!_interactionEnabled || !isVisible()) {
            return false;
        }

        const cocos2d::Vec2 worldPoint = touch->getLocation();
        const bool touched = getBoundingBox().containsPoint(worldPoint);
        if (touched) {
            stopActionByTag(101);
            cocos2d::ActionInterval* pressAnim = cocos2d::ScaleTo::create(0.06f, 1.04f);
            pressAnim->setTag(101);
            runAction(pressAnim);
        }
        return touched;
    };

    _touchListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        CC_UNUSED_PARAM(touch);
        CC_UNUSED_PARAM(event);
        stopActionByTag(101);
        cocos2d::ActionInterval* releaseAnim = cocos2d::ScaleTo::create(0.06f, 1.0f);
        releaseAnim->setTag(101);
        runAction(releaseAnim);

        if (_onClickCallback != nullptr && _interactionEnabled) {
            _onClickCallback(_cardId);
        }
    };

    _touchListener->onTouchCancelled = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        CC_UNUSED_PARAM(touch);
        CC_UNUSED_PARAM(event);
        stopActionByTag(101);
        cocos2d::ActionInterval* releaseAnim = cocos2d::ScaleTo::create(0.06f, 1.0f);
        releaseAnim->setTag(101);
        runAction(releaseAnim);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

} // namespace qipai
