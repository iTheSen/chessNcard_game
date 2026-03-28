#ifndef QIPAI_MODELS_GAME_MODEL_H
#define QIPAI_MODELS_GAME_MODEL_H

#include <unordered_map>
#include <vector>

#include "models/CardModel.h"

namespace qipai {

/**
 * @brief 游戏运行时总模型。
 *
 * 管理所有卡牌实体、主牌区、堆牌区与当前顶部手牌状态。
 */
class GameModel {
public:
    /**
     * @brief 添加主牌区卡牌。
     */
    void addPlayFieldCard(const CardModel& card);

    /**
     * @brief 添加堆牌区卡牌。
     */
    void addStackCard(const CardModel& card);

    /**
     * @brief 查找可写卡牌数据。
     */
    CardModel* findCard(int cardId);

    /**
     * @brief 查找只读卡牌数据。
     */
    const CardModel* findCard(int cardId) const;

    /**
     * @brief 获取所有主牌区卡牌 ID。
     */
    const std::vector<int>& getPlayFieldCardIds() const;

    /**
     * @brief 获取所有堆牌区卡牌 ID。
     */
    const std::vector<int>& getStackCardIds() const;

    /**
     * @brief 获取所有卡牌 ID。
     */
    std::vector<int> getAllCardIds() const;

    /**
     * @brief 是否还能从堆牌区抽牌。
     */
    bool canDrawFromStack() const;

    /**
     * @brief 获取下一张可抽堆牌 ID。
     */
    int peekNextStackCardId() const;

    /**
     * @brief 获取当前手牌顶部卡牌 ID。
     */
    int getTrayTopCardId() const;

    /**
     * @brief 设置当前手牌顶部卡牌 ID。
     */
    void setTrayTopCardId(int cardId);

    /**
     * @brief 获取下一张可抽堆牌的索引。
     */
    int getNextStackIndex() const;

    /**
     * @brief 设置下一张可抽堆牌的索引。
     */
    void setNextStackIndex(int index);

    /**
     * @brief 序列化为 JSON 对象。
     */
    rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief 从 JSON 对象反序列化。
     */
    static GameModel fromJson(const rapidjson::Value& value);

private:
    /** @brief 全量卡牌数据字典。 */
    std::unordered_map<int, CardModel> _cards;

    /** @brief 主牌区卡牌 ID 列表。 */
    std::vector<int> _playFieldCardIds;

    /** @brief 堆牌区卡牌 ID 列表。 */
    std::vector<int> _stackCardIds;

    /** @brief 当前手牌顶部卡牌 ID。 */
    int _trayTopCardId = -1;

    /** @brief 下一张可抽堆牌索引。 */
    int _nextStackIndex = 0;
};

} // namespace qipai

#endif // QIPAI_MODELS_GAME_MODEL_H
