#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine.h"
#include "State/CharacterJumpState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"

class Character : public Entity
{
public:
    static Character* getInstance(EntityInfo* info);
    static void addCharacter(EntityInfo* info);
    static int getNumberOfCharacters();
    static Character* getCharacter(int index);
private:
    static Character* _instance;
    static std::vector<Character*> _characters;
    bool init(EntityInfo* info) override;
    bool loadAnimations() override;
    StateMachine* _stateMachine;
protected:
    bool callbackOnContactBegin(PhysicsContact& contact);
    void callbackOnContactSeparate(PhysicsContact& contact);
    bool _isOnGround;
    void update(float dt) override;
};

#endif // !__CHARACTER_H__