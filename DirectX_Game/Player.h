#pragma once
#include"SimpleMath.h"
#include<d3d11.h>
#include "Graphics.h"
#include"CollisionHandler.h"
#include"Keyboard.h"
#include "Texture.h"
#include"Animation.h"
#include "PlayerMovement.h"
using namespace DirectX::SimpleMath;
class Player
{
public:
	ID3D11Buffer* vertexBuffer;
	Vector3 GetPosition();
	void Update(float deltaTime);
	void CreateIndexBuffer(Graphics* graphics);
	Player(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler);
	Player();
	void UpdateAnimation();

private:

	std::unique_ptr<DirectX::Keyboard> keyboard;
	Texture texture;
	BoxCollider* attackCollider;
	ID3D11Buffer* indexBuffer;
	ShaderClass* shaders;
	Graphics* graphics;
	Vector3 position;
	Animation* currentAnimation;
	ID3D11Buffer* currentAnimationBuffer;
	PlayerMovement* playerMovement;
	float attackRange = 1;
	float attackHeight = 1;
	float width = 2;
	float height = 2;
	float deltaTime;

	void Attack();

	void InitializeShaders();
	void CreateDrawable();
};