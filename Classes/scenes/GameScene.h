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

    /** @brief 游戏总控制器。 */
    std::unique_ptr<GameController> _gameController;
};

} // namespace qipai

#endif // QIPAI_SCENES_GAME_SCENE_H
