#include "LevelBlock.h"

LevelBlock::LevelBlock()
{
}

LevelBlock::LevelBlock(Vector2 pos, float width, float height, Graphics* graphics)
{
	this->position = pos;
	dimensions.height = height;
	dimensions.width = width;
}

