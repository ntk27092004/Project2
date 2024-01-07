#include "EnemyChaseState.h"
#include "EnemyStateMachine.h"
#include "Character/Character.h"

void EnemyChaseState::enterState(Entity* owner) {
    State::enterState(owner);
    auto ani = AnimationCache::getInstance()
        ->getAnimation(_owner->getEntityInfo()->_entityName + "_Idle_Right");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    _owner->getModel()->runAction(animate);

}

    std::string EnemyChaseState::updateState() {
        Vec2 enemyPosition = _owner->getModel()->getPosition();
        Vec2 characterPosition;
        EntityInfo* characterInfo = new EntityInfo(1, "Hero");
        Character* character = Character::getInstance(characterInfo);
        if (character) {
            characterPosition = character->getPosition();
            const float chaseRange = 50.0f;
            log("X-%f, Y-%f", characterPosition.x, characterPosition.y);

            if (characterPosition.x > enemyPosition.x - chaseRange &&
                characterPosition.x < enemyPosition.x + chaseRange &&
                characterPosition.y > enemyPosition.y - chaseRange &&
                characterPosition.y < enemyPosition.y + chaseRange) {
            
                return "chase";
            }
 
        }
    }

void EnemyChaseState::exitState() {
    State::exitState();
}
