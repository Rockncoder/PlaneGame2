#ifndef __GameplayLayer__
#define __GameplayLayer__

#include "cocos2d.h"
using namespace cocos2d;


class GameplayLayer : public Layer
{
public:
	GameplayLayer();
	~GameplayLayer();
	void update();
	void addEnemy(Node *);
	void addBullet(Node *);
	void addPlayerBullet(Node *);
	bool checkCollision(Node* first, Node* second);
private:
	Size visibleSize;
	std::vector<Node*> enemies;
	std::vector<Node*> enemiesToBeDeleted;
	std::vector<Node*> enemyBullets;
	std::vector<Node*> enemyBulletsToBeDeleted;
	std::vector<Node*> playerBullets;
	std::vector<Node*> playerBulletsToBeDeleted;
};

#endif // __GameplayLayer__
