#ifndef QIPAI_UTILS_LAYOUT_CONSTANTS_H
#define QIPAI_UTILS_LAYOUT_CONSTANTS_H

#include "cocos2d.h"

namespace qipai {
namespace layout {

constexpr float kDesignWidth = 1080.0f;
constexpr float kDesignHeight = 2080.0f;
constexpr float kPlayFieldHeight = 1500.0f;
constexpr float kStackHeight = 580.0f;
constexpr float kCardMoveDuration = 0.22f;

inline cocos2d::Vec2 trayCardPosition()
{
    return cocos2d::Vec2(360.0f, 280.0f);
}

inline cocos2d::Vec2 stackCardPosition()
{
    return cocos2d::Vec2(760.0f, 280.0f);
}

inline cocos2d::Vec2 undoButtonPosition()
{
    return cocos2d::Vec2(960.0f, 280.0f);
}

} // namespace layout
} // namespace qipai

#endif // QIPAI_UTILS_LAYOUT_CONSTANTS_H
