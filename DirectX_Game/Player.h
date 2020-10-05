#pragma once
#include"SimpleMath.h"
#include<d3d11.h>
#include "Graphics.h"
using namespace DirectX::SimpleMath;
class Player
{
public:
	ID3D11Buffer* vertexBuffer;

	void Update(float deltaTime);
	Vector3 GetPosition();
	void CreateIndexBuffer(Graphics* graphics);
	Player(Vector3 pos,Graphics* graphics);
	Player();
private:
	ID3D11Buffer* indexBuffer;
	ShaderClass* shaders;
	float width = 1;
	float height = 1;
	Vector3 position;
};