#pragma once
#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H
#include <string>
#include "../models/LevelConfig.h"

// 关卡配置加载器
// 从 JSON 文件加载 → 生成 LevelConfig
class LevelConfigLoader
{
public:
    static LevelConfig loadLevel(const std::string& jsonFile);
};
#endif