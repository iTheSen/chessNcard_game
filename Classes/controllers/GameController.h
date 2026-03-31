#ifndef QIPAI_CONTROLLERS_GAME_CONTROLLER_H
#define QIPAI_CONTROLLERS_GAME_CONTROLLER_H

#include <string>
#include <unordered_set>
#include <vector>

#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "managers/UndoManager.h"
#include "models/GameModel.h"
#include "views/GameView.h"

namespace qipai {

/**
 * @brief 游戏总控制器。
 *
 * 管理初始化流程、用户点击流程、动画回调和回退流程。
 */
class GameController {
public:
    /**
     * @brief 初始化控制器。
     * @param gameView 游戏视图。
     * @param levelConfigPath 关卡配置文件路径。
     * @return 是否初始化成功。
     */
    bool init(GameView* gameView, const std::string& levelConfigPath);

private:
    /**
     * @brief 处理卡牌点击。
     */
    void handleCardClick(int cardId);

    /**
     * @brief 决议卡牌点击——路由并执行卡牌点击业务逻辑。
     */
    bool resolveCardClick(int cardId, UndoModel& outUndo, std::string& outError);

    /**
     * @brief 处理回退按钮点击。
     */
    void handleUndoClick();

    /**
     * @brief 按当前模型刷新全部视图状态。
     */
    void refreshViewFromModel();

    /**
     * @brief 刷新单张卡牌的视图状态。
     */
    void refreshSingleCardView(int cardId, int trayTopCardId, int nextStackCardId);

    /**
     * @brief 加载指定索引关卡。
     */
    bool loadLevelByIndex(int levelIndex);

    /**
     * @brief 关卡是否已清空主牌区。
     */
    bool isCurrentLevelCleared() const;

    /**
     * @brief 当前是否存在可匹配的主牌区卡牌。
     */
    bool hasOperablePlayFieldMatch() const;

    /**
     * @brief 在一次合法操作后检查并处理关卡推进。
     */
    void handleLevelProgressAfterAction();

    /**
     * @brief 重建主牌区可操作卡牌缓存（未被覆盖的牌）。
     */
    void rebuildOperablePlayFieldCardIds();

    /**
     * @brief 应用一条回退记录到模型。
     */
    void applyUndoRecord(const UndoModel& undoRecord);

    /**
     * @brief 刷新状态栏提示文案。
     */
    void refreshStatusText(const std::string& message);

    /** @brief 游戏总视图指针。 */
    GameView* _gameView = nullptr;

    /** @brief 运行时游戏模型。 */
    GameModel _gameModel;

    /** @brief 主牌区控制器。 */
    PlayFieldController _playFieldController;

    /** @brief 堆牌区控制器。 */
    StackController _stackController;

    /** @brief 回退管理器。 */
    UndoManager _undoManager;

    /** @brief 主牌区当前可操作卡牌 ID 集合。 */
    std::unordered_set<int> _operablePlayFieldCardIds;

    /** @brief 关卡配置路径列表。 */
    std::vector<std::string> _levelConfigPaths;

    /** @brief 当前关卡索引。 */
    int _currentLevelIndex = 0;

    /** @brief 是否正在播放动画。 */
    bool _isAnimating = false;
};

} // namespace qipai

#endif // QIPAI_CONTROLLERS_GAME_CONTROLLER_H
