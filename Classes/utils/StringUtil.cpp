#include "StringUtil.h"
#include <cstdarg>
#include <stdio.h>

std::string StringUtil::format(const char* fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);
    va_end(args);
    return std::string(buf);
}