#include "LevelConfigLoader.h"
#include "services/JsonParseService.h"

LevelConfig LevelConfigLoader::loadLevel(const std::string& jsonFile)
{
    LevelConfig config;

    // µ÷ÓÃ Service ½âÎö
    config.playFieldCards = JsonParseService::loadPlayFieldFromJson(jsonFile);
    config.stackCards = JsonParseService::loadStackFromJson(jsonFile);

    return config;
}