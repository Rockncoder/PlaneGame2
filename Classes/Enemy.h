#ifndef __EnemySprite__
#define __EnemySprite__

#include "cocos2d.h"
#include "GameplayLayer.h"

using namespace cocos2d;

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	static Enemy* createEnemy(GameplayLayer* _gameplayLayer);
	bool initEnemy(GameplayLayer* _gameplayLayer);
	void update();
	void shoot(float dt);
	void killMe();

	bool isDead;
	GameplayLayer* gameplayLayer;

private:
	
};

#endif // __EnemySprite__


