#include "Enemy.h"
#include "Utilities/AnimationUtils.h"
#include "DefineBitmask.h"

Enemy* Enemy::_instance;
std::vector<Enemy*> Enemy::_enemies;

Enemy* Enemy::getInstance(EntityInfo* info) {
    if (_instance == nullptr){
        _instance = new Enemy();
        _instance->init(info);
        _instance->retain();
    }
    return _instance;
}

void Enemy::addEnemy(EntityInfo* info)
{
    Enemy* _newEnemy = new Enemy();
    if (_newEnemy->init(info)) {
        _enemies.push_back(_newEnemy);
    }
    else {
        delete _newEnemy;
    }
}

int Enemy::getNumberOfEnemy()
{
    return _enemies.size();
}

Enemy* Enemy::getEnemy(int index)
{
    if (index >= 0 && index< _enemies.size()) {
        return _enemies[index];
 }
    return nullptr;
}

bool Enemy::init(EntityInfo* info)
{
    if (!Entity::init(info))
    {
        log("Init Enemy Failed!");
        return false;
    }
    _info = info;
    auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "_Idle_Down");
    auto animate = RepeatForever::create(Animate::create(aniIdle));
    _model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "_Idle_Down (1)");
    _model->runAction(animate);
    this->addChild(_model);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Enemy::callbackOnContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto physicBody = PhysicsBody::createBox(_model->getContentSize() / 3.3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicBody->setCategoryBitmask(DefineBitmask::ENEMY);
    physicBody->setCollisionBitmask(DefineBitmask::BULLET | DefineBitmask::CHARACTER);
    physicBody->setContactTestBitmask(DefineBitmask::BULLET | DefineBitmask::CHARACTER);
    physicBody->setRotationEnable(false);
    physicBody->setGravityEnable(false);
    this->setPhysicsBody(physicBody);
    _enemyStateMachine = StateMachine::create(this);
    _enemyStateMachine->addState("idle", new EnemyIdleState());
    _enemyStateMachine->addState("patrol", new EnemyPatrolState());
    _enemyStateMachine->addState("chase", new EnemyChaseState());
    _enemyStateMachine->setCurrentState("patrol");
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

bool Enemy::callbackOnContactBegin(PhysicsContact& contact)
{
    EntityInfo info(2, "Hero");
    auto enemy1 = Enemy::getInstance(&info);
    auto enemy1x1 = enemy1->getEnemy(0);
    enemy1x1->removeFromParentAndCleanup(false);
    return false;
}

