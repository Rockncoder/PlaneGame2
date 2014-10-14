#ifndef __Bullet__
#define __Bullet__

#include "cocos2d.h"
using namespace cocos2d;

class Bullet : public cocos2d::Sprite
{
public:
	Bullet();
	~Bullet();
	static Bullet* create(Vec2 point, int _type);
	bool init(Vec2 point, int _type);
	void update();
	bool isDead;
private:
	int type;
};

#endif