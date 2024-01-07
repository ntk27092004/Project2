#include "CharacterJumpState.h"
#include "StateMachine.h"
#include "../Character.h"
#include "../../Entity/Entity.h"
#include "KeyBoardInput.h"

void CharacterJumpState::enterState(Entity* owner)
{
    State::enterState(owner);
    log("jump state");
    auto ani = AnimationCache::getInstance()
        ->getAnimation(owner->getEntityInfo()->_entityName + "_Jump_Down");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    owner->getModel()->runAction(animate);
    auto mapNode = Director::getInstance()->getRunningScene()->getChildByTag(100);
    if (mapNode != nullptr) {
        _map = dynamic_cast<GameMap*>(mapNode);
    }
  
}

std::string CharacterJumpState::updateState()
{

    return "jump";
}

void CharacterJumpState::exitState()
{
    State::exitState();
}
