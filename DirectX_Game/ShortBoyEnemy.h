#pragma once
#include "Enemy.h"
class ShortBoyEnemy : public Enemy
{
public:
	ShortBoyEnemy(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler, int enemyIndex);

};