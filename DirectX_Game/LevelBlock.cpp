#include "LevelBlock.h"

LevelBlock::LevelBlock()
{
}

LevelBlock::LevelBlock(Vector3 pos, float width, float height, Graphics* graphics)
{
	this->position = pos;
	this->collider = new BoxCollider(pos, width, height);
	dimensions.height = height;
	dimensions.width = width;
	graphics->CreateConstantBuffer(&dimensionsBuffer, 16);

	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = graphics->deviceContext->Map(dimensionsBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &dimensions, sizeof(Dimensions));
	graphics->deviceContext->Unmap(dimensionsBuffer, 0);

	texture.Initialize(graphics->device, graphics->deviceContext, "BlockTileSet.png");
}

