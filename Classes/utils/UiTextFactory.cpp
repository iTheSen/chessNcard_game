#include "utils/UiTextFactory.h"

namespace qipai {
namespace ui {

namespace {

std::string resolveUiFontPath()
{
    const std::string bundledCjk = "fonts/HiraginoSansGB.ttc";
    if (cocos2d::FileUtils::getInstance()->isFileExist(bundledCjk)) {
        return bundledCjk;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    const std::string macCjk = "/System/Library/Fonts/Hiragino Sans GB.ttc";
    if (cocos2d::FileUtils::getInstance()->isFileExist(macCjk)) {
        return macCjk;
    }
#endif

    const std::string fallbackTtf = "fonts/arial.ttf";
    if (cocos2d::FileUtils::getInstance()->isFileExist(fallbackTtf)) {
        return fallbackTtf;
    }

    return "";
}

} // namespace

cocos2d::Label* createLabel(
    const std::string& text,
    float fontSize,
    const cocos2d::Color3B& color,
    bool withOutline)
{
    cocos2d::Label* label = nullptr;

    const std::string fontPath = resolveUiFontPath();
    if (!fontPath.empty()) {
        label = cocos2d::Label::createWithTTF(text, fontPath, fontSize);
    }

    if (label == nullptr) {
        label = cocos2d::Label::createWithSystemFont(text, "Arial", fontSize);
    }

    if (label == nullptr) {
        return nullptr;
    }

    label->setTextColor(cocos2d::Color4B(color));
    label->enableShadow(cocos2d::Color4B(0, 0, 0, 130), cocos2d::Size(0.0f, -2.0f), 1.0f);
    if (withOutline) {
        label->enableOutline(cocos2d::Color4B(0, 0, 0, 150), 2);
    }

    return label;
}

} // namespace ui
} // namespace qipai
