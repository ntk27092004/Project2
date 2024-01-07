#include "Enemy.h"
#include "Utilities/AnimationUtils.h"

Enemy* Enemy::create(EntityInfo* info)
{
    auto newObject = new Enemy();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Enemy::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "_Idle_Down");
    auto animate = RepeatForever::create(Animate::create(aniIdle));
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "_Idle_Down (1)");
    _model->runAction(animate);
    this->addChild(_model);
    _enemyStateMachine = EnemyStateMachine::create(this);
    _enemyStateMachine->addState("idle", new EnemyIdleState());
    _enemyStateMachine->addState("patrol", new EnemyPatrolState());
    _enemyStateMachine->addState("chase", new EnemyChaseState());
    this->addChild(_enemyStateMachine);
    return true;
}

bool Enemy::loadAnimations()
{
    Entity::loadAnimations();
    std::vector<std::string> aniNames;
    aniNames.push_back(_info->_entityName + "_Idle_Down");
    aniNames.push_back(_info->_entityName + "_Idle_Right");
    aniNames.push_back(_info->_entityName + "_Jump_Down");

    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Hero/", name);
        AnimationUtils::createAnimation(name, 2.0f);
    }

    return true;
}

