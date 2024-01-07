#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Entity/Entity.h"
#include "EnemyStateMachine.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyPatrolState.h"


class Enemy : public Entity
{
public:
	static Enemy* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
protected:
	bool loadAnimations() override;
	EnemyStateMachine* _enemyStateMachine;

};
#endif // !__ENEMY_H__
