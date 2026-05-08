#pragma once
#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>

// 字符串工具
class StringUtil
{
public:
    // 格式化字符串
    static std::string format(const char* fmt, ...);
};
#endif