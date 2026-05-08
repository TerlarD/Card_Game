#include "JsonParseService.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
#include "utils/FileUtil.h"

using namespace rapidjson;
USING_NS_CC;

std::vector<CardModel> JsonParseService::loadPlayFieldFromJson(const std::string& jsonFile)
{
    std::vector<CardModel> res;
    if (!isJsonFileExist(jsonFile)) return res;

    std::string content = FileUtils::getInstance()->getStringFromFile(jsonFile);
    Document doc;
    doc.Parse(content.c_str());

    if (!doc.IsObject() || !doc.HasMember("Playfield")) return res;

    int cardId = 1;
    auto& arr = doc["Playfield"].GetArray();
    for (SizeType i = 0; i < arr.Size(); i++)
    {
        auto& item = arr[i];
        CardModel m;
        m.cardId = cardId++;
        m.face = (CardFaceType)item["CardFace"].GetInt();
        m.suit = (CardSuitType)item["CardSuit"].GetInt();
        m.x = item["Position"]["x"].GetFloat();
        m.y = item["Position"]["y"].GetFloat();
        m.isOpened = true;
        m.isInStack = false;
        res.push_back(m);
    }
    return res;
}

std::vector<CardModel> JsonParseService::loadStackFromJson(const std::string& jsonFile)
{
    std::vector<CardModel> res;
    if (!isJsonFileExist(jsonFile)) return res;

    std::string content = FileUtils::getInstance()->getStringFromFile(jsonFile);
    Document doc;
    doc.Parse(content.c_str());

    if (!doc.IsObject() || !doc.HasMember("Stack")) return res;

    int cardId = 100;
    auto& arr = doc["Stack"].GetArray();
    for (SizeType i = 0; i < arr.Size(); i++)
    {
        auto& item = arr[i];
        CardModel m;
        m.cardId = cardId++;
        m.face = (CardFaceType)item["CardFace"].GetInt();
        m.suit = (CardSuitType)item["CardSuit"].GetInt();
        m.x = 540;
        m.y = 250;
        m.isOpened = true;
        m.isInStack = true;
        res.push_back(m);
    }
    return res;
}

bool JsonParseService::isJsonFileExist(const std::string& jsonFile)
{
    return FileUtil::isFileExist(jsonFile);
}