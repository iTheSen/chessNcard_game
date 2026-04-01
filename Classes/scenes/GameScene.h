#ifndef QIPAI_SCENES_GAME_SCENE_H
#define QIPAI_SCENES_GAME_SCENE_H

#include <memory>

#include "cocos2d.h"
#include "controllers/GameController.h"

namespace qipai {

/**
 * @brief 游戏主场景。
 *
 * 作为入口场景负责创建并组装 GameView 与 GameController。
 */
class GameScene : public cocos2d::Scene {
public:
    /**
     * @brief 创建场景对象。
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief 初始化场景。
     */
    bool init() override;

    CREATE_FUNC(GameScene);

private:
    /** @brief 游戏总视图。 */
    qipai::GameView* _gameView = nullptr;

    /*
    Scene
    ├── View（cocos对象，Ref管理）
    └── Controller（C++对象，unique_ptr管理）
    */
   /** 
    * @brief 游戏总控制器。
    * @note 唯一拥有者（unique_ptr），生命周期由 GameScene 管理
    */
    std::unique_ptr<GameController> _gameController;
};

} // namespace qipai

#endif // QIPAI_SCENES_GAME_SCENE_H
