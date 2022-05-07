#include "ShortBoyEnemy.h"

ShortBoyEnemy::ShortBoyEnemy(Vector3 pos, Graphics* graphics, int enemyIndex)
	:Enemy(pos,graphics)
{
	this->height = 2;
	this->width = 2;
	this->modelWidth = 0.8f;
	this->modelHeight = 1.2f;
	this->attackRange = 1.2f;
	this->attackHeight = 1;
	Init(enemyIndex, "Textures/Small_Enemy_SpriteSheet.png");
}
