#pragma once
#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>

// 卡牌图片资源配置（所有图片路径统一管理）
struct CardResConfig
{
    // 牌背 & 牌面基底
    std::string cardBack = "res/card_general.png";
    std::string cardFrontBase = "res/card_general.png";

    // 花色图片
    std::string suitClubs = "res/suits/club.png";
    std::string suitDiamonds = "res/suits/diamond.png";
    std::string suitHearts = "res/suits/heart.png";
    std::string suitSpades = "res/suits/spade.png";

    // 红色点数（红桃、方块）
    std::string numberRedA = "res/number/big_red_A.png";
    std::string numberRed2 = "res/number/big_red_2.png";
    std::string numberRed3 = "res/number/big_red_3.png";
    std::string numberRed4 = "res/number/big_red_4.png";
    std::string numberRed5 = "res/number/big_red_5.png";
    std::string numberRed6 = "res/number/big_red_6.png";
    std::string numberRed7 = "res/number/big_red_7.png";
    std::string numberRed8 = "res/number/big_red_8.png";
    std::string numberRed9 = "res/number/big_red_9.png";
    std::string numberRed10 = "res/number/big_red_10.png";
    std::string numberRedJ = "res/number/big_red_J.png";
    std::string numberRedQ = "res/number/big_red_Q.png";
    std::string numberRedK = "res/number/big_red_K.png";

    // 黑色点数（梅花、黑桃）
    std::string numberBlackA = "res/number/big_black_A.png";
    std::string numberBlack2 = "res/number/big_black_2.png";
    std::string numberBlack3 = "res/number/big_black_3.png";
    std::string numberBlack4 = "res/number/big_black_4.png";
    std::string numberBlack5 = "res/number/big_black_5.png";
    std::string numberBlack6 = "res/number/big_black_6.png";
    std::string numberBlack7 = "res/number/big_black_7.png";
    std::string numberBlack8 = "res/number/big_black_8.png";
    std::string numberBlack9 = "res/number/big_black_9.png";
    std::string numberBlack10 = "res/number/big_black_10.png";
    std::string numberBlackJ = "res/number/big_black_J.png";
    std::string numberBlackQ = "res/number/big_black_Q.png";
    std::string numberBlackK = "res/number/big_black_K.png";
};
#endif