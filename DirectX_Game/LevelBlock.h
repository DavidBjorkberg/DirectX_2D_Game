#pragma once
#include"Shaders.h"
#include"SimpleMath.h"
#include"BoxCollider.h"
using namespace DirectX::SimpleMath;
class LevelBlock
{
public:
	LevelBlock();
	LevelBlock(Vector3 pos, float width, float height);
	ID3D11Buffer* vertexBuffer;
	BoxCollider* collider;
private:
	Vector3 position;
};