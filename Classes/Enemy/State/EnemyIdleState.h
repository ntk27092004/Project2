#ifndef __ENEMY_IDLE_STATE_H__
#define __ENEMY_IDLE_STATE_H__

#include "State.h"
#include "Character/Character.h"

class EnemyIdleState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
	Character* _character;
};

#endif // !__ENEMY_IDLE_STATE_H__
