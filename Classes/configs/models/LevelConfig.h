#pragma once
#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H

#include <vector>
#include "models/CardModel.h"

// πÿø®æ≤Ã¨≈‰÷√
struct LevelConfig
{
    std::vector<CardModel> playFieldCards;
    std::vector<CardModel> stackCards;
    int levelId = 1;
};

#endif