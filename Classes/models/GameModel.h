#pragma once
#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include "../models/CardModel.h"

struct GameModel
{
    std::vector<CardModel> playFieldCards;
    std::vector<CardModel> stackCards;
    CardModel currentTopCard;
};

#endif