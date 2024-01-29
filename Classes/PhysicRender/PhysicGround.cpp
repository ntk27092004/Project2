#include "PhysicGround.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;

void PhysicGround::initializeLines(Node* parent, TMXObjectGroup* objectGroup)
{
    if (objectGroup) {
        auto objects = objectGroup->getObjects();
        for (const auto& object : objects) {
            ValueMap lineInfo = object.asValueMap();
            float x = lineInfo["x"].asFloat();
            float y = lineInfo["y"].asFloat();
            float width = lineInfo["width"].asFloat();
            float height = lineInfo["height"].asFloat();
            Vec2 origin(x, y);
            Vec2 topLeft(x, y + height);
            Vec2 topRight(x + width, y + height);
            auto lineNode = Node::create();
            auto physicsBody = PhysicsBody::createBox(Size(width, height));
            physicsBody->setCategoryBitmask(DefineBitmask::GROUND);
            physicsBody->setCollisionBitmask(DefineBitmask::CHARACTER | DefineBitmask::ENEMY);
            physicsBody->setContactTestBitmask(DefineBitmask::CHARACTER);
            physicsBody->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsBody->setDynamic(false);
            lineNode->setPhysicsBody(physicsBody);
            lineNode->setPosition(origin);
            lineNode->setTag(TAG_GROUND);
            parent->addChild(lineNode);
        }
    }
}








