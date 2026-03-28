#ifndef QIPAI_UTILS_UI_TEXT_FACTORY_H
#define QIPAI_UTILS_UI_TEXT_FACTORY_H

#include <string>

#include "cocos2d.h"

namespace qipai {
namespace ui {

/**
 * @brief 创建统一风格的文本标签。
 *
 * 自动选择可用字体并附加基础描边、阴影样式。
 */
cocos2d::Label* createLabel(
    const std::string& text,
    float fontSize,
    const cocos2d::Color3B& color = cocos2d::Color3B::WHITE,
    bool withOutline = true);

} // namespace ui
} // namespace qipai

#endif // QIPAI_UTILS_UI_TEXT_FACTORY_H
