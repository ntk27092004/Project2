#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine.h"
#include "State/CharacterJumpState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"
//#include "Map/GameMap.h"

class Character : public Entity
{
public:
	static Character* getInstance(EntityInfo* info);
	static Character* create(EntityInfo* info);
	bool init(EntityInfo* info) override;

protected:
	static Character* _instance;
	bool loadAnimations() override;
	StateMachine* _stateMachine;
};

#endif // !__CHARACTER_H__
