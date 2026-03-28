/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

/**
 * @brief 旧工程兼容场景壳。
 *
 * 该类保留用于兼容历史工程文件中的编译入口，实际运行时会转发到 qipai::GameScene。
 */
class HelloWorld : public cocos2d::Scene
{
public:
    /**
     * @brief 创建场景对象。
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief 初始化场景对象。
     */
    virtual bool init();
    
    /**
     * @brief 退出回调。
     */
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    /**
     * @brief Cocos2d-x 默认 create 宏。
     */
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
