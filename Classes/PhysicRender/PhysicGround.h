#ifndef __PHYSIC_GROUND_H__
#define __PHYSIC_GROUND_H__

#include "cocos2d.h"
#include "2d/CCTMXObjectGroup.h"
USING_NS_CC;

class PhysicGround : public Node {
public:
    static void initializeLines(Node* parent, TMXObjectGroup* objectGroup);
    static const int TAG_GROUND = 10;
};

#endif // !__PHYSIC_GROUND_H__
