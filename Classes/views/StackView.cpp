#include "views/StackView.h"

#include <new>

#include "utils/LayoutConstants.h"
#include "utils/UiTextFactory.h"

namespace qipai {

namespace {

void drawSlot(cocos2d::DrawNode* drawNode, const cocos2d::Vec2& center, const cocos2d::Color4F& tint)
{
    const cocos2d::Vec2 half(102.0f, 152.0f);
    const cocos2d::Vec2 minPoint = center - half;
    const cocos2d::Vec2 maxPoint = center + half;

    drawNode->drawSolidRect(minPoint, maxPoint, cocos2d::Color4F(0.06f, 0.12f, 0.20f, 0.56f));
    drawNode->drawSolidRect(
        minPoint + cocos2d::Vec2(4.0f, 4.0f),
        maxPoint - cocos2d::Vec2(4.0f, 4.0f),
        cocos2d::Color4F(tint.r, tint.g, tint.b, 0.16f));
    drawNode->drawRect(minPoint, maxPoint, cocos2d::Color4F(0.90f, 0.95f, 1.0f, 0.85f));
    drawNode->drawRect(
        minPoint + cocos2d::Vec2(4.0f, 4.0f),
        maxPoint - cocos2d::Vec2(4.0f, 4.0f),
        cocos2d::Color4F(1.0f, 1.0f, 1.0f, 0.28f));
}

} // namespace

StackView* StackView::create()
{
    StackView* view = new (std::nothrow) StackView();
    if (view == nullptr) {
        return nullptr;
    }

    if (!view->init()) {
        delete view;
        return nullptr;
    }

    view->autorelease();
    return view;
}

bool StackView::init()
{
    if (!Node::init()) {
        return false;
    }

    cocos2d::LayerGradient* background = cocos2d::LayerGradient::create(
        cocos2d::Color4B(32, 57, 84, 255),
        cocos2d::Color4B(17, 33, 54, 255),
        cocos2d::Vec2(0.0f, -1.0f));
    background->setContentSize(cocos2d::Size(layout::kDesignWidth, layout::kStackHeight));
    background->setIgnoreAnchorPointForPosition(false);
    background->setAnchorPoint(cocos2d::Vec2::ZERO);
    background->setPosition(cocos2d::Vec2::ZERO);
    addChild(background, 0);

    const cocos2d::Vec2 trayPos = layout::trayCardPosition();
    const cocos2d::Vec2 stackPos = layout::stackCardPosition();
    const cocos2d::Vec2 undoPos = layout::undoButtonPosition();

    cocos2d::DrawNode* panelLine = cocos2d::DrawNode::create();
    panelLine->drawLine(
        cocos2d::Vec2(0.0f, layout::kStackHeight - 1.0f),
        cocos2d::Vec2(layout::kDesignWidth, layout::kStackHeight - 1.0f),
        cocos2d::Color4F(0.90f, 0.96f, 1.0f, 0.82f));
    addChild(panelLine, 1);

    cocos2d::DrawNode* slots = cocos2d::DrawNode::create();
    drawSlot(slots, trayPos, cocos2d::Color4F(0.18f, 0.59f, 0.94f, 1.0f));
    drawSlot(slots, stackPos, cocos2d::Color4F(0.95f, 0.56f, 0.24f, 1.0f));
    addChild(slots, 1);

    cocos2d::Label* trayText = ui::createLabel(u8"\u624B\u724C\u9876\u90E8", 30.0f, cocos2d::Color3B(219, 236, 255), true);
    if (trayText == nullptr) {
        return false;
    }
    trayText->setPosition(cocos2d::Vec2(trayPos.x, 58.0f));
    addChild(trayText, 2);

    cocos2d::Label* stackText = ui::createLabel(u8"\u5907\u7528\u724C", 30.0f, cocos2d::Color3B(255, 230, 203), true);
    if (stackText == nullptr) {
        return false;
    }
    stackText->setPosition(cocos2d::Vec2(stackPos.x, 58.0f));
    addChild(stackText, 2);

    cocos2d::DrawNode* undoBackground = cocos2d::DrawNode::create();
    undoBackground->drawSolidRect(
        undoPos - cocos2d::Vec2(92.0f, 40.0f),
        undoPos + cocos2d::Vec2(92.0f, 40.0f),
        cocos2d::Color4F(0.17f, 0.43f, 0.67f, 0.95f));
    undoBackground->drawRect(
        undoPos - cocos2d::Vec2(92.0f, 40.0f),
        undoPos + cocos2d::Vec2(92.0f, 40.0f),
        cocos2d::Color4F(0.92f, 0.97f, 1.0f, 0.90f));
    addChild(undoBackground, 2);

    cocos2d::Label* undoLabel = ui::createLabel(
        u8"\u21A9 \u56DE\u9000",
        32.0f,
        cocos2d::Color3B(237, 246, 255),
        true);
    if (undoLabel == nullptr) {
        return false;
    }
    cocos2d::MenuItemLabel* undoItem = cocos2d::MenuItemLabel::create(undoLabel, [this](cocos2d::Ref* sender) {
        CC_UNUSED_PARAM(sender);
        if (_undoCallback != nullptr) {
            _undoCallback();
        }
    });

    cocos2d::Menu* menu = cocos2d::Menu::create(undoItem, nullptr);
    menu->setPosition(undoPos);
    addChild(menu, 3);

    return true;
}

void StackView::setUndoCallback(const std::function<void()>& callback)
{
    _undoCallback = callback;
}

} // namespace qipai
