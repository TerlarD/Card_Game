#include "GameModelGenerator.h"

static int s_cardIdCounter = 0;

GameModel GameModelGenerator::generateFromConfig(const LevelConfig& config)
{
    GameModel model;

    // 复制主牌区卡牌
    model.playFieldCards = config.playFieldCards;
    initializeCardIds(model.playFieldCards);

    // 复制备用牌堆卡牌
    model.stackCards = config.stackCards;
    initializeCardIds(model.stackCards);

    // 设置初始底牌（备用牌堆的最后一张）
    if (!model.stackCards.empty())
    {
        model.currentTopCard = model.stackCards.back();
    }

    return model;
}

void GameModelGenerator::initializeCardIds(std::vector<CardModel>& cards)
{
    for (auto& card : cards)
    {
        card.cardId = generateCardId();
    }
}

int GameModelGenerator::generateCardId()
{
    return ++s_cardIdCounter;
}