#include "LevelBlock.h"

LevelBlock::LevelBlock()
{
}

LevelBlock::LevelBlock(Vector3 pos, float width, float height)
{
	this->position = pos;
	this->collider = BoxCollider(pos, width, height);
}

