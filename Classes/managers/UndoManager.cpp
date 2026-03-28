#include "managers/UndoManager.h"

namespace qipai {

void UndoManager::pushRecord(const UndoModel& record)
{
    _records.push_back(record);
}

bool UndoManager::popRecord(UndoModel& outRecord)
{
    if (_records.empty()) {
        return false;
    }

    outRecord = _records.back();
    _records.pop_back();
    return true;
}

bool UndoManager::canUndo() const
{
    return !_records.empty();
}

int UndoManager::size() const
{
    return static_cast<int>(_records.size());
}

void UndoManager::clear()
{
    _records.clear();
}

} // namespace qipai
