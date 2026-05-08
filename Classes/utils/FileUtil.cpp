#include "FileUtil.h"
#include "cocos2d.h"

using namespace cocos2d;

bool FileUtil::isFileExist(const std::string& path)
{
    return FileUtils::getInstance()->isFileExist(path);
}

std::string FileUtil::getFullPath(const std::string& path)
{
    return FileUtils::getInstance()->fullPathForFilename(path);
}