
#include "GameplayLayer.h"
#include "Enemy.h"
#include "Bullet.h"

GameplayLayer::GameplayLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();
}

GameplayLayer::~GameplayLayer()
{
}

void GameplayLayer::update()
{
	// update all of the enemy's position and check for any which need to be deleted
	for each (Node* enemy in enemies)
	{
		((Enemy*)enemy)->update();
		if (enemy->getPositionX() + enemy->getContentSize().width / 2 < 0 && !((Enemy*)enemy)->isDead)
		{
			enemiesToBeDeleted.push_back(enemy);
		}
	}

	// remove any to be deleted enemies
	for each (Node* enemy in enemiesToBeDeleted)
	{
		auto ndx = std::find(enemies.begin(), enemies.end(), enemy);
		enemies.erase(ndx);
		this->removeChild(enemy, true);
	}
	enemiesToBeDeleted.clear();

	// update all of the bullets' position and check for any which need to be deleted
	for each (Node* bullet in enemyBullets)
	{
		((Bullet*)bullet)->update();
		if (bullet->getPositionX() + bullet->getContentSize().width / 2 < 0)
		{
			enemyBulletsToBeDeleted.push_back(bullet);
		}
	}

	// remove any to be deleted enemies
	for each (Node* bullet in enemyBulletsToBeDeleted)
	{
		auto ndx = std::find(enemyBullets.begin(), enemyBullets.end(), bullet);
		enemyBullets.erase(ndx);
		this->removeChild(bullet, true);
	}
	enemyBulletsToBeDeleted.clear();

	// update all of the bullets' position and check for any which need to be deleted
	for each (Node* bullet in playerBullets)
	{
		((Bullet*)bullet)->update();
		if (bullet->getPositionX() > visibleSize.width)
		{
			playerBulletsToBeDeleted.push_back(bullet);
		}
	}

	for each (Node* bullet in playerBullets)
	{
		for each (Node* enemy in enemies)
		{
			if (!((Enemy*)enemy)->isDead && !((Bullet*)bullet)->isDead && checkCollision(bullet, enemy))
			{
				//this->removeChild((Bullet*)bullet);
				playerBulletsToBeDeleted.push_back(bullet);
				enemiesToBeDeleted.push_back(enemy);
				((Enemy*)enemy)->isDead = true;
				((Bullet*)bullet)->isDead = true;
			}
		}
	}


	// remove any to be deleted player bullets
	for each (Node* bullet in playerBulletsToBeDeleted)
	{
		auto ndx = std::find(playerBullets.begin(), playerBullets.end(), bullet);
		playerBullets.erase(ndx);
		this->removeChild(bullet, true);
	}
	playerBulletsToBeDeleted.clear();

	if (enemiesToBeDeleted.size() > 1)
	{
		CCLOG("Possible error");
	}


}

void GameplayLayer::addEnemy(Node *enemy)
{
	enemies.push_back(enemy);
}

void GameplayLayer::addBullet(Node *bullet)
{
	enemyBullets.push_back(bullet);
}

void  GameplayLayer::addPlayerBullet(Node *bullet)
{
	playerBullets.push_back(bullet);
}

bool GameplayLayer::checkCollision(Node* first, Node* second)
{
	Rect box1 = first->boundingBox();
	Rect box2 = second->boundingBox();
	return box1.intersectsRect(box2);
}


