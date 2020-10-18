#include "LevelBlock.h"

LevelBlock::LevelBlock()
{
}

LevelBlock::LevelBlock(Vector3 pos, float width, float height, Graphics* graphics)
{
	this->position = pos;
	this->collider = new BoxCollider(pos, width, height, -1);
	dimensions.height = height;
	dimensions.width = width;
	graphics->CreateConstantBuffer(&dimensionsBuffer, 16);

	graphics->MapToBuffer(dimensionsBuffer, &dimensions, sizeof(Dimensions));
	texture.Initialize(graphics->device, graphics->deviceContext, "Textures/BlockTileSet.png");
}

