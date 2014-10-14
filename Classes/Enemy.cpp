
#include "Enemy.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"



Enemy::Enemy()
{
	isDead = false;
}


Enemy::~Enemy()
{
}

Enemy* Enemy::createEnemy(GameplayLayer* _gameplayLayer)
{
	Enemy* ob = new Enemy();
	if (ob && ob->initEnemy(_gameplayLayer))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}

bool Enemy::initEnemy(GameplayLayer* _gameplayLayer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	gameplayLayer = _gameplayLayer;

	float mrand = rand() % 3 + 1;
	CCLOG("random height %f", mrand);

	float h = visibleSize.height * mrand * 0.25;
	this->initWithFile("enemyPlane.png");
	auto p = Vec2(visibleSize.width - this->getContentSize().width / 2, h);
	this->setPosition(p);
	return true;
}

void Enemy::update()
{
	Vec2 newPosition;
	Vec2::add(this->getPosition(), Vec2(-3, 0), &newPosition);
	this->setPosition(newPosition);
}

void Enemy::shoot(float dt)
{
	auto point = this->getPosition();
	point.x -= this->getContentSize().width / 2;
	point.y -= this->getContentSize().height * 0.05;
	Bullet* bullet = Bullet::create(point, 1);
	gameplayLayer->addChild(bullet);
	gameplayLayer->addBullet(bullet);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("143611__d-w__weapons-synth-blast-01.wav");

}