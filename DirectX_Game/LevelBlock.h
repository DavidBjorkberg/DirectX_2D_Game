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
	LevelBlock();
	LevelBlock(Vector2 pos, float width, float height, Graphics* graphics);
	Vector2 position;
	Dimensions dimensions;
};