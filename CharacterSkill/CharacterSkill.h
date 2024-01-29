#ifndef __CHARACTER_SKILL_H__
#define __CHARACTER_SKILL_H__

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class CharacterSkill : public Node {
public:
	static CharacterSkill* create(std::string skillName);
	virtual bool init(std::string skillName);
protected:
	Sprite* _model;
protected:
	bool callbackOnContactBegin(PhysicsContact& contact);
	CC_SYNTHESIZE(Entity*, _owner, Owner);
};

#endif // !__CHARACTER_SKILL_H__
