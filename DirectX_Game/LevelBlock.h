#pragma once
#include"Shaders.h"
#include"SimpleMath.h"
#include"BoxCollider.h"
#include "Texture.h"
#include"Graphics.h"
using namespace DirectX::SimpleMath;
class LevelBlock
{
public:
	struct Dimensions
	{
		float width;
		float height;
	};
	ID3D11Buffer* dimensionsBuffer;
	BoxCollider* collider;
	Texture texture;
	Vector2 position;
	Dimensions dimensions;
	LevelBlock();
	LevelBlock(Vector2 pos, float width, float height, Graphics* graphics);
private:

};