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
	std::vector<int> GetEnemyHitIndices();
	Vector3 GetPosition();
	void UpdateAnimation();
	void Update(float deltaTime);
	void CreateIndexBuffer(Graphics* graphics);
	Player(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler);
	Player();

private:
	Animation* jumpAnimation;//
	Animation* idleAnimation;//
	Animation* runAnimation;// 
	Animation* attackAnimation;// 
	std::unique_ptr<DirectX::Keyboard> keyboard;
	Texture texture;
	ID3D11Buffer* indexBuffer;
	ShaderClass* shaders;
	Graphics* graphics;
	Vector3 position;
	Animation* currentAnimation;
	ID3D11Buffer* currentAnimationBuffer;
	PlayerMovement* playerMovement;
	std::vector<int> hitEnemyIndices;
	float width = 2;
	float height = 2;
	float deltaTime;
	bool isAttacking;
	void Attack();

	void InitializeShaders();
	void CreateDrawable();
};