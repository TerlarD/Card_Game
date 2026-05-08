#include "NodeUtil.h"

using namespace cocos2d;

void NodeUtil::removeAllChildren(Node* node)
{
    if (!node) return;
    node->removeAllChildrenWithCleanup(true);
}

void NodeUtil::setVisibleRecursive(Node* node, bool visible)
{
    if (!node) return;
    node->setVisible(visible);
    for (auto child : node->getChildren())
        setVisibleRecursive(child, visible);
}