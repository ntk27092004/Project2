#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraFlow.h"
#include "audio/include/AudioEngine.h"
#include "Enemy/Enemy.h"
#include "Character/Character.h"
USING_NS_CC;


Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -100));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/*ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setContentSize(Size(200, 200));
	scrollView->setBackGroundImage("bg.jpg", ui::Widget::TextureResType::LOCAL);
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setScrollBarEnabled(false);
	scrollView->setBounceEnabled(true);*/

	//this->addChild(scrollView, 3);

	//auto originalImage = Sprite::create("Maps/Image/Background/Green.png");
	//auto imageSize = originalImage->getContentSize();

	//int numberOfClonesX = 10; // Số lượng sao chép
	//float xOffset = imageSize.width; // Khoảng cách giữa các bản sao theo trục x

	//for (int i = 0; i < numberOfClonesX; ++i) {
	//	auto clonedImageX = Sprite::createWithTexture(originalImage->getTexture());
	//	clonedImageX->setPosition(Vec2(imageSize.width * i + imageSize.width / 2, visibleSize.height / 2));
	//	this->addChild(clonedImageX);
	//}

	//int numberOfClonesY = 10;
	//float yOffset = imageSize.height; // Khoảng cách giữa các bản sao theo trục x

	//for (int i = 0; i < numberOfClonesY; ++i) {
	//	auto clonedImageY = Sprite::createWithTexture(originalImage->getTexture());
	//	clonedImageY->setPosition(Vec2(visibleSize.width / 2, imageSize.height * i + imageSize.height / 2));
	//	this->addChild(clonedImageY);
	//}

	auto metaStart = Vec2(visibleSize.width/4  - 500, visibleSize.height/ 4);
	auto metaEnd = Vec2(visibleSize.width/4 + 500, visibleSize.height/ 4);
	auto metaNode = Node::create();
	auto metaBody = PhysicsBody::createEdgeSegment(metaStart, metaEnd);
	metaNode->setPhysicsBody(metaBody);
	this->addChild(metaNode);

	auto backGround = Sprite::create("BackGround.png");
	backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround);

	auto moveToUp = MoveTo::create(2, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	auto moveToDown = MoveTo::create(2, Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto sequence = Sequence::create(moveToUp, moveToDown, nullptr);
	auto repeatMove = RepeatForever::create(sequence);

	backGround->runAction(repeatMove);


	_keyboard = KeyboardInput::getInstance();
	_keyboard->addKey(EventKeyboard::KeyCode::KEY_SPACE);

	_gameMap = GameMap::create("/Maps/map1.tmx");
	_gameMap->setTag(100);
	this->addChild(_gameMap);

	_character = Character::create(new EntityInfo(1, "Hero"));

	auto enemy = Enemy::create(new EntityInfo(2, "Hero"));
	enemy->setPosition(Director::getInstance()->getVisibleSize() / 2);

	this->addChild(enemy, 1);

	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");
	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();
	_character->setPosition(position);
	/*auto characterSize = _character->getModel()->getContentSize();
	auto characterBody = PhysicsBody::createBox(Size(characterSize.width/2.5, characterSize.height/2.5), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	_character->getModel()->setPhysicsBody(characterBody);*/
	this->addChild(_character, 1);

	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{
	Vec2 currentPosition = _character->getPosition();
	//log("Character Position - X: %f, Y: %f", currentPosition.x, currentPosition.y);
}


void HelloWorld::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();
	Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto mapSize = _gameMap->getContentSize();
	Rect boundingBox = { size.width / 2,size.height / 2,mapSize.width - size.width / 2 - size.width / 2,mapSize.height - size.height / 2 - size.height / 2 };
	CameraFollow* cam = CameraFollow::create(_character, boundingBox);
	this->addChild(cam);

	this->addChild(KeyboardInput::getInstance());
}

