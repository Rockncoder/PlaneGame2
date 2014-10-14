#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	fireCountDown = 0;
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = LabelTTF::create("Hello SVCC", "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	LayerColor::initWithColor(Color4B(140, 140, 200, 255));

	leftButton = Rect::Rect(0, 0, visibleSize.width / 2, visibleSize.height);
	rightButton = Rect::Rect(visibleSize.width / 2, 0, visibleSize.width / 2, visibleSize.height);

	hero = Sprite::create("playerPlane.png");
	hero->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.5));
	this->addChild(hero, 5);

	gameplayLayer = new GameplayLayer();
	this->addChild(gameplayLayer);

	auto accelListener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(accelListener, this);
	Device::setAccelerometerEnabled(true);

	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	touchListener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	touchListener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	this->setTouchEnabled(true);

	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);

	this->scheduleUpdate();

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mainMainMusic.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mainMainMusic.wav", true);
	//CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.75);

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("83560__nbs-dark__ship-fire.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("143611__d-w__weapons-synth-blast-01.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("95078__sandyrb__the-crash.wav");

	return true;
}

void HelloWorld::update(float dt)
{
	float maxY = visibleSize.height - hero->getContentSize().height / 2;
	float minY = hero->getContentSize().height / 2;
	float distStep = (distFraction * dt);
	float newY = hero->getPosition().y + distStep;
	newY = MIN(MAX(newY, minY), maxY);
	hero->setPosition(Vec2(hero->getPosition().x, newY));
	gameplayLayer->update();
}

void HelloWorld::spawnEnemy(float dt)
{
	CCLOG("spawn enemy");
	Enemy* enemy = Enemy::createEnemy(gameplayLayer);
	gameplayLayer->addChild(enemy);
	gameplayLayer->addEnemy(enemy);
	enemy->shoot(0.016);
}

void HelloWorld::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *unused_event)
{
	distFraction = visibleSize.height * acc->x;
	//	CCLOG("accelerometer: %f, %f", acc->x, acc->y);
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	// get the first touch point
	Touch *touch = touches.at(0);
	cocos2d::Point location = touch->getLocationInView();
	// converts from screen coordinates to Open GL coordinates
	location = Director::getInstance()->convertToGL(location);
	if (rightButton.containsPoint(location) && fireCountDown == 0)
	{
		CCLOG("FIRE!!!");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("83560__nbs-dark__ship-fire.wav");
		shootBullet();
		fireCountDown = 2;
	}
	if (fireCountDown > 0){ fireCountDown--; }
}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch *> &pTouches, cocos2d::Event* unused_event)
{
	//	CCLOG("TouchesMoved");
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch *> &pTouches, cocos2d::Event* unused_event)
{
	//	CCLOG("TouchesEnded");
}

void HelloWorld::shootBullet()
{
	auto point = hero->getPosition();
	point.x += hero->getContentSize().width / 2;
	point.y -= hero->getContentSize().height * 0.05;
	Bullet* bullet = Bullet::create(point, 2);
	gameplayLayer->addChild(bullet);
	gameplayLayer->addPlayerBullet(bullet);
}


