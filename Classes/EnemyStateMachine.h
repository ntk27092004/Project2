#ifndef __ENEMY_STATE_MACHINE_H__
#define __ENEMY_STATE_MACHINE_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "State.h"
USING_NS_CC;

class EnemyStateMachine : public Node
{
public:
	static const int EnemyAnimationTag = 10;
public:
	static EnemyStateMachine* create(Entity* entity);

	virtual bool init(Entity* entity);
	virtual void addState(std::string stateName,State* state);
protected:
	Entity* _entityTarget;
	std::map<std::string, State*> _states;

	std::string _currentState;
protected:
	void update(float dt) override;
	void onEnter() override;
};

#endif // !__ENEMY_STATE_MACHINE_H__
