#ifndef __ENEMY_CHASE_STATE_H__
#define __ENEMY_CHASE_STATE_H__

#include "State.h"
#include "Map/GameMap.h"
#include "Character/Character.h"
#include "Entity/Entity.h"

class EnemyChaseState : public State {
public:
    void enterState(Entity* owner) override;
    std::string updateState() override;
    void exitState() override;
private:
    float _chaseRange = 0.0000001f;
};

#endif // __ENEMY_CHASE_STATE_H__
