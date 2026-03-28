#include "HelloWorldScene.h"

#include "scenes/GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return qipai::GameScene::createScene();
}

bool HelloWorld::init()
{
    return Scene::init();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    CC_UNUSED_PARAM(pSender);
    Director::getInstance()->end();
}

// Legacy project compatibility:
// proj.win32/proj.ios_mac still compile HelloWorldScene.cpp by default.
// To avoid manually editing those project files, include the new module .cpp files
// here so legacy projects can link all new symbols.
#include "configs/models/LevelConfig.cpp"
#include "configs/loaders/LevelConfigLoader.cpp"
#include "configs/models/CardResConfig.cpp"

#include "models/CardModel.cpp"
#include "models/GameModel.cpp"
#include "models/UndoModel.cpp"

#include "managers/UndoManager.cpp"

#include "services/GameRuleService.cpp"
#include "services/GameModelFromLevelGenerator.cpp"
#include "services/CardSpriteComposerService.cpp"

#include "views/CardView.cpp"
#include "views/PlayFieldView.cpp"
#include "views/StackView.cpp"
#include "views/GameView.cpp"

#include "controllers/PlayFieldController.cpp"
#include "controllers/StackController.cpp"
#include "controllers/GameController.cpp"

#include "scenes/GameScene.cpp"
