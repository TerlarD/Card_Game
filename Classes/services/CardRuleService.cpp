#include "CardRuleService.h"
#include <cstdlib> // abs()

bool CardRuleService::canCardMatch(const CardModel& cardA, const CardModel& cardB)
{
    int faceA = (int)cardA.face;
    int faceB = (int)cardB.face;
    return abs(faceA - faceB) == 1;
}

bool CardRuleService::isValidCard(const CardModel& card)
{
    return card.face >= CFT_ACE && card.face <= CFT_KING
        && card.suit >= CST_CLUBS && card.suit <= CST_SPADES;
}