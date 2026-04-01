#ifndef QIPAI_MANAGERS_UNDO_MANAGER_H
#define QIPAI_MANAGERS_UNDO_MANAGER_H

#include <vector>

#include "models/UndoModel.h"

namespace qipai {

/**
 * @brief 回退管理器。
 * 
 * 维护回退栈，提供压栈、出栈与清空能力。容器使用 vector,存储 UndoModel
 */
class UndoManager {
public:
    /**
     * @brief 压入一条回退记录。
     */
    void pushRecord(const UndoModel& record);

    /**
     * @brief 弹出一条回退记录。
     * @param outRecord 输出的回退记录。
     * @return 是否成功弹出。
     */
    bool popRecord(UndoModel& outRecord);

    /**
     * @brief 判断是否可回退。
     */
    bool canUndo() const;

    /**
     * @brief 获取回退记录数量。
     */
    int size() const;

    /**
     * @brief 清空回退记录。
     */
    void clear();

private:
    /** @brief 回退记录栈。 */
    std::vector<UndoModel> _records;
};

} // namespace qipai

#endif // QIPAI_MANAGERS_UNDO_MANAGER_H
