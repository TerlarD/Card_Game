#pragma once
#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H
#include <string>

// 全局游戏静态配置（所有写死的数据全部放这里）
struct GameConfig
{
    // 设计分辨率
    int designWidth = 1080;
    int designHeight = 2080;

    // 区域尺寸
    int playFieldHeight = 1500;
    int stackHeight = 580;

    // 手牌堆顶部牌坐标
    float stackCardX = 540;
    float stackCardY = 250;

    // 动画时间
    float cardMoveDuration = 0.25f;

    // 按钮文字
    std::string undoBtnText = "UNDO";

    // 字体
    std::string fontName = "fonts/Marker Felt.ttf";
    float btnFontSize = 45;
};
#endif