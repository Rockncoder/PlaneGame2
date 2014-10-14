#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameplayLayer.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	cocos2d::Size visibleSize;
	cocos2d::Sprite* hero;
	float distFraction;
	cocos2d::Rect leftButton, rightButton;
	GameplayLayer* gameplayLayer;
	int fireCountDown;

	virtual void update(float dt);
	virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);
	void fireBullet();

	void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);

	void spawnEnemy(float dt);
	void shootBullet();

};

#endif // __HELLOWORLD_SCENE_H__
