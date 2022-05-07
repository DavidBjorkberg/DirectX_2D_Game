#include "TallBoyEnemy.h"

TallBoyEnemy::TallBoyEnemy(Vector3 pos, Graphics* graphics, int enemyIndex) 
	: Enemy(pos,graphics)
{
	this->height = 2;
	this->width = 2;
	this->modelWidth = 0.6f;
	this->modelHeight = 1.2f;
	this->attackRange = 1.2f;
	this->attackHeight = 1;
	Init(enemyIndex, "Textures/Enemy_SpriteSheet.png");
}
