#include "scenes/GameScene.h"

#include <new>

#include "views/GameView.h"

namespace qipai {

cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    // Scene::init负责拼接View和初始化
    if (!Scene::init()) {
        return false;
    }

    _gameView = GameView::create();
    if (_gameView == nullptr) {
        return false;
    }

    addChild(_gameView, 1);

    _gameController = std::unique_ptr<GameController>(new (std::nothrow) GameController());
    if (_gameController == nullptr) {
        return false;
    }

    if (!_gameController->init(_gameView, "configs/levels/level_1.json")) {
        return false;
    }

    return true;
}

} // namespace qipai
