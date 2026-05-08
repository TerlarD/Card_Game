#pragma once
#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include <vector>
#include "models/UndoModel.h"

class UndoManager
{
private:
    std::vector<UndoModel> _undoList;
public:
    UndoManager() {}
    ~UndoManager() {}

    void pushRecord(const UndoModel& model);
    UndoModel popRecord();
    bool hasUndoRecord() const;
    void clearAll();
};

#endif