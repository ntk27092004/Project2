#include "HorizontalLayout.h"

bool HorizontalLayout::init()
{
    if (!Node::init())
    {
        log("Init HorizontalLayout failed!");
        return false;
    }


    return true;
}

void HorizontalLayout::alignment()
{
    if (_parent == nullptr) return;

    auto children = _parent->getChildren();
    children.eraseObject(this);

    float xDistance = _parent->getContentSize().width / (float)children.size();

    for (int i = 0; i < children.size(); ++i)
    {
        children.at(i)->setPositionX(i * xDistance);
    }
}
