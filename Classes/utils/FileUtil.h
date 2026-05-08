#pragma once
#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include <string>

// 文件工具
class FileUtil
{
public:
    static bool isFileExist(const std::string& path);
    static std::string getFullPath(const std::string& path);
};
#endif