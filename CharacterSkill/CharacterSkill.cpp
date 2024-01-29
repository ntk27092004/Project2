#include "CharacterSkill.h"
#include "DefineBitmask.h"
#include "IDamageable.h"

CharacterSkill* CharacterSkill::create(std::string skillName)
{
	auto newObject = new CharacterSkill();
	if (newObject != nullptr && newObject->init(skillName)) {
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool CharacterSkill::init(std::string skillName)
{
	if (!Node::init()) {
		return false;
	}
	_model = Sprite::create( skillName + ".png");
	this->addChild(_model);
	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1), 1.0f);
	body->setCategoryBitmask(DefineBitmask::BULLET);
	body->setCollisionBitmask(DefineBitmask::NON);
	body->setContactTestBitmask(/*DefineBitmask::CHARACTER |*/ DefineBitmask::ENEMY);
	this->setPhysicsBody(body);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(CharacterSkill::callbackOnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool CharacterSkill::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? (nodeB) : (nodeA);

	log("a: %d | b: %d", nodeA->getPhysicsBody()->getCategoryBitmask()
		, nodeB->getPhysicsBody()->getCategoryBitmask());
	log("a & b: %d", (nodeA->getPhysicsBody()->getCategoryBitmask() | nodeB->getPhysicsBody()->getCategoryBitmask()));

	/*auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr)
	{
		damageable->takeDamage(_owner);
	}*/

	this->removeFromParentAndCleanup(true);

	return false;
}
