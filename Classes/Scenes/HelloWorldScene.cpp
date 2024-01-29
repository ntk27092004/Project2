#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraFlow.h"
#include "audio/include/AudioEngine.h"
#include "Enemy/Enemy.h"
#include "Character/Character.h"
#include "CharacterSkill/CharacterSkill.h"
#include "DefineBitmask.h"
#include "PhysicRender/PhysicGround.h"
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

	/*auto backGround = Sprite::create("BackGround.png");
	backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround);

	auto moveToUp = MoveTo::create(2, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	auto moveToDown = MoveTo::create(2, Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto sequence = Sequence::create(moveToUp, moveToDown, nullptr);
	auto repeatMove = RepeatForever::create(sequence);

	backGround->runAction(repeatMove);*/


	_gameMap = GameMap::create("/Maps/map1.tmx");
	_gameMap->setTag(100);
	this->addChild(_gameMap);

	std::vector<EntityInfo*> enemyInfoList;

	for (int i = 0; i < 10; i++) {
		EntityInfo* info = new EntityInfo(2, "Hero");
		enemyInfoList.push_back(info);

		auto enemy = Enemy::getInstance(info);
		enemy->addEnemy(info);

		auto enemyInstance = enemy->getEnemy(i);

		float xPos = (origin.x + 100) + 100 * i;
		enemyInstance->setPosition(Vec2(xPos, 100));

		this->addChild(enemyInstance);
	}

	//auto objLine = _gameMap->getObjectGroup("PhysicLine");
	//if (objLine) {
	//	auto objects = objLine->getObjects();
	//	for (const auto object : objects) {
	//		ValueMap Line = object.asValueMap();
	//		Vec2 positionLine;
	//		positionLine.x = Line["x"].asFloat();
	//		positionLine.y = Line["y"].asFloat();

	//		float width = Line["width"].asFloat();
	//		float height = Line["height"].asFloat();
	//		Vec2 topLeft(positionLine.x, positionLine.y + height);
	//		Vec2 topRight(positionLine.x + width, positionLine.y + height);
	//		Vec2 origin(positionLine.x, positionLine.y);
	//		auto lineNode = Node::create();

	//		auto physicsBody = PhysicsBody::createEdgeBox(Size(width, height));
	//		physicsBody->setPositionOffset(Vec2(width * 0.5f, height * 0.5f)); 
	//		//physicsBody->setGravityEnable(false);
	//		lineNode->setPhysicsBody(physicsBody);
	//		lineNode->setPosition(origin);

	//		this->addChild(lineNode);
	//	}
	//}
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);

	auto objLine = _gameMap->getObjectGroup("PhysicLine");
	PhysicGround::initializeLines(this, objLine);


		auto listener = EventListenerMouse::create();
		listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


		EntityInfo* info = new EntityInfo(1, "Hero");
		_character = Character::getInstance(info);
		_character->addCharacter(info);

		int num = _character->getNumberOfCharacters();
		log("number of characters: %d", num);
		auto _char = _character->getCharacter(0);
		TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
		ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");
		Vec2 position;
		position.x = charPoint["x"].asFloat();
		position.y = charPoint["y"].asFloat();
		_char->setPosition(position);

		this->addChild(_char, 1);

		this->scheduleUpdate();
		return true;
	}


	void HelloWorld::update(float dt)
	{
		
	}


	void HelloWorld::onEnter()
{
	Scene::onEnter();
	auto _char = _character->getCharacter(0);
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();
	Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto mapSize = _gameMap->getContentSize();
	Rect boundingBox = { size.width / 8,size.height / 8,mapSize.width - size.width / 8 - size.width / 8,mapSize.height - size.height / 8 - size.height / 8 };
	CameraFollow* cam = CameraFollow::create(_char, boundingBox);
	this->addChild(cam);

	this->addChild(KeyboardInput::getInstance());
}
void HelloWorld::onMouseDown(EventMouse* event)
{
	auto char1 = _character->getCharacter(0);
	
	Vec2 camPos = Camera::getDefaultCamera()->getPosition();
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 mousPos = camPos - visibleSize / 2 + event->getLocationInView();

	Vec2 direction = mousPos - char1->getPosition();
	direction.normalize();
	
	auto bullet = CharacterSkill::create("bullet");

	bullet->setPosition(char1->getPosition());
	bullet->getPhysicsBody()->setVelocity(direction * 300);
	bullet->setOwner(char1);

	this->addChild(bullet, 1);
}



