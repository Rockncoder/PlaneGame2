
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

Bullet* Bullet::create(Vec2 point, int _type)
{
	Bullet* ob = new Bullet();
	if (ob && ob->init(point, _type))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}

bool Bullet::init(Vec2 point, int _type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	type = _type;
	if (type == 1)
	{
		this->initWithFile("enemyBullet.png");
	}
	else
	{
		this->initWithFile("playerBullet.png");
	}
	isDead = false;
	this->setPosition(point);
	return true;
}

void Bullet::update()
{
	Vec2 newPosition;
	if (type == 1)
	{
		Vec2::add(this->getPosition(), Vec2(-7, 0), &newPosition);
	}
	else
	{
		Vec2::add(this->getPosition(), Vec2(7, 0), &newPosition);
	}
	this->setPosition(newPosition);
}