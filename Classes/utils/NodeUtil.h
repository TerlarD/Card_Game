#pragma once
#ifndef NODE_UTIL_H
#define NODE_UTIL_H
#include "cocos2d.h"

// 节点工具
class NodeUtil
{
public:
    static void removeAllChildren(cocos2d::Node* node);
    static void setVisibleRecursive(cocos2d::Node* node, bool visible);
};
#endif