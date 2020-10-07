#pragma once
#include"SimpleMath.h"
#include<d3d11.h>
#include "Graphics.h"
#include"CollisionHandler.h"
#include"Keyboard.h"
using namespace DirectX::SimpleMath;
class Player
{
public:
	ID3D11Buffer* vertexBuffer;
	Vector3 GetPosition();
	void Update(float deltaTime,DirectX::Keyboard::State kb);
	void CreateIndexBuffer(Graphics* graphics);
	Player(Vector3 pos,Graphics* graphics, CollisionHandler* collisionHandler);
	Player();
private:
	float gravity = 2;
	float movementSpeed = 2;
	Vector3 velocity;
	CollisionHandler* collisionHandler;
	BoxCollider* collider;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* moveBuffer;
	ShaderClass* shaders;
	Graphics* graphics;
	Vector3 previousTranslation;
	Matrix moveMatrix = Matrix::Identity;
	Vector3 position;
	float width = 1;
	float height = 1;
	void Move(float deltaTime);
	void CalculateVelocity(DirectX::Keyboard::State kb, float deltaTime);
};