#include "views/PlayFieldView.h"

#include <new>

#include "utils/LayoutConstants.h"
#include "utils/UiTextFactory.h"

namespace qipai {

PlayFieldView* PlayFieldView::create()
{
    PlayFieldView* view = new (std::nothrow) PlayFieldView();
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

bool PlayFieldView::init()
{
    if (!Node::init()) {
        return false;
    }

    cocos2d::LayerGradient* background = cocos2d::LayerGradient::create(
        cocos2d::Color4B(21, 117, 67, 255),
        cocos2d::Color4B(8, 72, 43, 255),
        cocos2d::Vec2(0.0f, -1.0f));
    background->setContentSize(cocos2d::Size(layout::kDesignWidth, layout::kPlayFieldHeight));
    background->setIgnoreAnchorPointForPosition(false);
    background->setAnchorPoint(cocos2d::Vec2::ZERO);
    background->setPosition(cocos2d::Vec2(0.0f, layout::kStackHeight));
    addChild(background, 0);

    cocos2d::DrawNode* feltLines = cocos2d::DrawNode::create();
    for (int i = 1; i <= 6; ++i) {
        const float t = static_cast<float>(i) / 7.0f;
        const float y = layout::kStackHeight + layout::kPlayFieldHeight * t;
        feltLines->drawLine(
            cocos2d::Vec2(0.0f, y),
            cocos2d::Vec2(layout::kDesignWidth, y),
            cocos2d::Color4F(1.0f, 1.0f, 1.0f, 0.035f));
    }
    addChild(feltLines, 1);

    cocos2d::LayerColor* headerBar = cocos2d::LayerColor::create(
        cocos2d::Color4B(7, 48, 33, 145),
        layout::kDesignWidth,
        128.0f);
    headerBar->setIgnoreAnchorPointForPosition(false);
    headerBar->setAnchorPoint(cocos2d::Vec2::ZERO);
    headerBar->setPosition(cocos2d::Vec2(0.0f, layout::kDesignHeight - 128.0f));
    addChild(headerBar, 2);

    cocos2d::DrawNode* border = cocos2d::DrawNode::create();
    border->drawRect(
        cocos2d::Vec2(0.0f, layout::kStackHeight),
        cocos2d::Vec2(layout::kDesignWidth, layout::kDesignHeight),
        cocos2d::Color4F(0.95f, 0.98f, 0.96f, 0.75f));
    addChild(border, 3);

    cocos2d::Label* title = ui::createLabel(u8"\u4E3B\u724C\u533A", 46.0f, cocos2d::Color3B(236, 250, 242), true);
    if (title == nullptr) {
        return false;
    }
    title->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
    title->setPosition(cocos2d::Vec2(26.0f, layout::kDesignHeight - 20.0f));
    addChild(title, 4);

    cocos2d::Label* hint = ui::createLabel(
        u8"\u53EF\u64CD\u4F5C\u724C\uFF1A\u70B9\u6570\u4E0E\u624B\u724C\u9876\u90E8\u76F8\u5DEE 1",
        24.0f,
        cocos2d::Color3B(198, 232, 213),
        false);
    if (hint != nullptr) {
        hint->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
        hint->setPosition(cocos2d::Vec2(28.0f, layout::kDesignHeight - 82.0f));
        addChild(hint, 4);
    }

    return true;
}

} // namespace qipai
