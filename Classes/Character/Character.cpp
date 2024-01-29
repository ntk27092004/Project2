#include "Character.h"
#include "Utilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "PhysicRender/PhysicGround.h"
#include "Enemy/Enemy.h"

std::vector<Character*> Character::_characters;
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


bool Character::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Character failed!");
		return false;
	}
	_info = info;
	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "_Idle_Down");
	auto animate = RepeatForever::create(Animate::create(aniIdle));
	_model = Sprite::createWithSpriteFrameName("./" + _info->_entityName + "_Idle_Down (1)");
	_model->runAction(animate);
	this->addChild(_model);

	auto physicBody = PhysicsBody::createBox(_model->getContentSize() / 3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicBody->setCategoryBitmask(DefineBitmask::CHARACTER);
	physicBody->setCollisionBitmask(DefineBitmask::ENEMY | DefineBitmask::GROUND);
	physicBody->setContactTestBitmask(DefineBitmask::ENEMY | DefineBitmask::GROUND);
	physicBody->setRotationEnable(false);
	physicBody->setGravityEnable(true);
	this->setPhysicsBody(physicBody);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Character::callbackOnContactBegin, this);
	listener->onContactSeparate = CC_CALLBACK_1(Character::callbackOnContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	


	_stateMachine = StateMachine::create(this);
	_stateMachine->addState("idle", new CharacterIdleState());
	_stateMachine->addState("run", new CharacterRunState());
	_stateMachine->addState("jump", new CharacterRunState());
	_stateMachine->setCurrentState("idle");
	this->addChild(_stateMachine);
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


void Character::addCharacter(EntityInfo* info) {
	Character* _newCharacter = new Character();
	if (_newCharacter->init(info)) {
		_characters.push_back(_newCharacter);
	}
	else {
		delete _newCharacter;
	}
}

Character* Character::getCharacter(int index) {
	if (index >= 0 && index < _characters.size()) {
		return _characters[index];
	}
	return nullptr;
}

int Character::getNumberOfCharacters() {
	return _characters.size();
}

bool Character::callbackOnContactBegin(PhysicsContact& contact) {
	
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;
	auto target = (nodeA == this) ? (nodeB) : (nodeA); // Lấy đối tượng kia (không phải nhân vật)
		if (target->getTag() == PhysicGround::TAG_GROUND && target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::GROUND) {
			_isOnGround = true;
			
		}

	return false; // Trả về true để tiếp tục xử lý va chạm
}

void Character::callbackOnContactSeparate(PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return;
	auto target = (nodeA == this) ? (nodeB) : (nodeA); // Lấy đối tượng kia (không phải nhân vật)
	if (target->getTag() == PhysicGround::TAG_GROUND && target->getPhysicsBody()->getCategoryBitmask() & DefineBitmask::GROUND) {
		_isOnGround = false;
	}
}

void Character::update(float dt) {
	if (_isOnGround) {
		log("Character is on the ground");
		this->getPhysicsBody()->setGravityEnable(false);
	}
}




