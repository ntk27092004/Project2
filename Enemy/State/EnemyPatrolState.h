#ifndef __ENEMY_PATROL_STATE_H__
#define __ENEMY_PATROL_STATE_H__

#include "State.h"
#include "Map/GameMap.h"
#include "Character/Character.h"
class EnemyPatrolState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
};

#endif // !__ENEMY_PATROL_STATE_H__
