#pragma once
#ifndef CARD_RULE_SERVICE_H
#define CARD_RULE_SERVICE_H

#include "../models/CardModel.h"

// 卡牌规则服务：无状态、不持有数据、只提供业务计算
class CardRuleService
{
public:
    // 判断两张牌是否可以匹配（点数差1）
    static bool canCardMatch(const CardModel& cardA, const CardModel& cardB);

    // 判断牌是否是有效牌（用于扩展：大小王、癞子等）
    static bool isValidCard(const CardModel& card);
};

#endif