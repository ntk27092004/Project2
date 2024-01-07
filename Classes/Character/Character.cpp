#include "Character.h"
#include "Utilities/AnimationUtils.h"

Character* Character::_instance;

Character* Character::getInstance(EntityInfo* info)
{
	if (_instance == nullptr)
	{
		_instance = new Character();
		_instance->init(info);
		_instance->retain();

	}
	return _instance;
}

Character* Character::create(EntityInfo* info)
{
	auto newObject = new Character();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Character::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Character failed!");
		return false;
	}

	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "_Idle_Down");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "_Idle_Down (1)");
	_model->runAction(animate);
	this->addChild(_model);

	_stateMachine = StateMachine::create(this);
	_stateMachine->addState("idle", new CharacterIdleState());
	_stateMachine->addState("run", new CharacterRunState());
	_stateMachine->addState("jump", new CharacterRunState());

	this->addChild(_stateMachine);
	_info = info;
	return true;
}

bool Character::loadAnimations()
{
	Entity::loadAnimations();

	std::vector<std::string> aniNames;
	aniNames.push_back(_info->_entityName + "_Idle_Down");
	aniNames.push_back(_info->_entityName + "_Idle_Right");
	aniNames.push_back(_info->_entityName + "_Jump_Down");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Hero/", name);
		AnimationUtils::createAnimation(name, 1.0f);
	}

	return true;
}