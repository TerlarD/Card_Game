#pragma once
#ifndef JSON_PARSE_SERVICE_H
#define JSON_PARSE_SERVICE_H

#include <vector>
#include "cocos2d.h"
#include "models/CardModel.h"

USING_NS_CC;

// JSON 配置解析服务：无状态、静态方法、不持有数据
class JsonParseService
{
public:
    // 解析桌面牌
    static std::vector<CardModel> loadPlayFieldFromJson(const std::string& jsonFile);

    // 解析备用牌堆
    static std::vector<CardModel> loadStackFromJson(const std::string& jsonFile);

    // 判断文件是否存在
    static bool isJsonFileExist(const std::string& jsonFile);
};

#endif