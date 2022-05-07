#pragma once
#include"SimpleMath.h"
#include"Animation.h"
#include"CollisionHandler.h"
#include"Keyboard.h"
#include "Component.h"
using namespace DirectX::SimpleMath;
class PlayerMovement : public Component
{
public:
	Vector2 position;
	ID3D11Buffer* moveBuffer;
	ID3D11Buffer* facingDirBuffer;
	CollisionHandler* collisionHandler;
	bool canMove = true;

	void Update(float deltaTime) override;
	bool IsGrounded();
	PlayerMovement(Vector2 position, float width, float height,CollisionHandler* collisionHandler,Graphics* graphics, DirectX::Keyboard* keyboard);
private:
	enum class VelocityMode
	{
		Add,
		Set
	};
	DirectX::Keyboard* keyboard;
	Graphics* graphics;

	Vector2 curVelocity;
	Vector2 previousTranslation;
	Matrix moveMatrix = Matrix::Identity;
	float attackRange = 1;
	float attackHeight = 1;
	bool canJump = true; 
	bool facingRight = true; 
	float gravity = 6; 
	float jumpForce = 9; 
	float maxXVelocity = 5; 
	float acceleration = 10; 
	float deltaTime;

	void Move(); 
	void Jump(); 
	void CheckNextFrameCollision(); 
	void AddVelocity(Vector2 newVelocity, VelocityMode velocityMode); 
	void ApplyGravity(); 
	void ClampVelocity(); 
	void SwitchFacingDir(); 
	void GetInput();

};