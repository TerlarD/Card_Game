#include "UndoManager.h"

void UndoManager::pushRecord(const UndoModel& model)
{
    _undoList.push_back(model);
}

UndoModel UndoManager::popRecord()
{
    UndoModel empty;
    if (_undoList.empty())
        return empty;

    UndoModel last = _undoList.back();
    _undoList.pop_back();
    return last;
}

bool UndoManager::hasUndoRecord() const
{
    return !_undoList.empty();
}

void UndoManager::clearAll()
{
    _undoList.clear();
}