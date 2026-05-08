#pragma once
#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include "../models/CardModel.h"

enum UndoType
{
    UNDO_MATCH_CARD,
    UNDO_STACK_NEXT
};

struct UndoModel
{
    UndoType type;

    // 被操作的牌
    CardModel card;

    // 操作前后的顶部牌
    CardModel oldTop;
    CardModel newTop;

    // 被操作牌的原始位置
    float cardOldX;
    float cardOldY;

    // 顶部牌的位置
    float topOldX;
    float topOldY;

    // 操作前的备用牌堆状态
    std::vector<CardModel> oldStackCards;
};

#endif