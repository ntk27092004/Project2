#include "DemoPhysic.h"

bool DemoPhysic::init()
{
	if (!Scene::initWithPhysics())
	{
		log("Init DemoPhysic failed!");
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -500));

	auto edgeBox = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(
		Director::getInstance()->getVisibleSize(),PhysicsMaterial(1, 0.5 ,1), 3);
	edgeBox->setPosition(Director::getInstance()->getVisibleSize() / 2);
	edgeBox->setPhysicsBody(edgeBody);
	this->addChild(edgeBox);

	_character = Sprite::create("CloseNormal.png");
	_character->setPosition(Director::getInstance()->getWinSize() / 2);
	auto body = PhysicsBody::createCircle(
		_character->getContentSize().width / 2, PhysicsMaterial(0, 1, 1));
	body->setMass(0.5f);
	_character->setPhysicsBody(body);
	this->addChild(_character);

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(DemoPhysic::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void DemoPhysic::onMouseDown(EventMouse* event)
{
	//Vec2 mousPos = event->getLocationInView();
	//float speed = 300;
	//Vec2 direction = mousPos - _character->getPosition();
	//direction.normalize();

	//// create bullet
	//auto bullet = Sprite::create("default.png");
	//bullet->setPosition(_character->getPosition());

	//auto body = PhysicsBody::createCircle(bullet->getContentSize().width / 2,PhysicsMaterial(1, 0, 1));
	//bullet->setPhysicsBody(body);
	//bullet->getPhysicsBody()->setGravityEnable(false);
	//bullet->getPhysicsBody()->setVelocity(direction * speed);

	//this->addChild(bullet);

	_character->getPhysicsBody()->applyForce(Vec2(0, 1) * 7000);
}