#pragma once
#ifndef GAME_MODEL_GENERATOR_H
#define GAME_MODEL_GENERATOR_H

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

/**
 * @brief 游戏模型生成服务
 *
 * 负责将静态配置（LevelConfig）转换为动态运行时数据（GameModel），
 * 处理卡牌初始化逻辑和游戏状态设置。
 */
class GameModelGenerator
{
public:
    /**
     * @brief 从关卡配置生成游戏模型
     * @param config 关卡配置
     * @return 生成的游戏模型
     */
    static GameModel generateFromConfig(const LevelConfig& config);

    /**
     * @brief 初始化卡牌ID
     * @param cards 卡牌列表
     */
    static void initializeCardIds(std::vector<CardModel>& cards);

private:
    /**
     * @brief 生成唯一卡牌ID
     * @return 唯一ID
     */
    static int generateCardId();
};

#endif // GAME_MODEL_GENERATOR_H