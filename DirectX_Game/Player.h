#pragma once
#include"SimpleMath.h"
#include<d3d11.h>
#include "Graphics.h"
#include"CollisionHandler.h"
#include"Keyboard.h"
#include "Texture.h"
#include"Animation.h"
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
	void UpdateAnimation();

private:
	enum class VelocityMode
	{
		Add,
		Set
	};
	Texture texture;
	Vector3 curVelocity;
	CollisionHandler* collisionHandler;
	BoxCollider* collider;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* moveBuffer;
	ShaderClass* shaders;
	Graphics* graphics;
	Vector3 previousTranslation;
	Matrix moveMatrix = Matrix::Identity;
	Vector3 position;
	Animation* jumpAnimation;
	Animation* idleAnimation;
	Animation* currentAnimation;
	ID3D11Buffer* currentAnimationBuffer;
	bool canJump = true;
	float gravity = 6;
	float width = 2;
	float height = 2;
	float jumpForce = 9;
	float maxXVelocity = 5;
	float acceleration =10;
	float deltaTime;
	void Move();
	void Jump();
	void CheckNextFrameCollision();
	void AddVelocity(Vector3 newVelocity, VelocityMode velocityMode);
	void ApplyGravity(DirectX::Keyboard::State kb);
	void GetInput(DirectX::Keyboard::State kb);
	bool IsGrounded();
	void ClampVelocity();
	void InitializeShaders();
	void CreateDrawable();
};