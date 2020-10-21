#pragma once
#include"SimpleMath.h"
#include"Animation.h"
#include"CollisionHandler.h"
#include"Keyboard.h"

using namespace DirectX::SimpleMath;
class PlayerMovement
{
public:
	Vector3 position;
	ID3D11Buffer* moveBuffer;
	ID3D11Buffer* facingDirBuffer;
	CollisionHandler* collisionHandler;
	BoxCollider* collider;
	BoxCollider* attackCollider;
	bool canMove = true;

	void Update(float deltaTime, Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer);
	bool IsGrounded();
	PlayerMovement(Vector3 position, float width, float height,CollisionHandler* collisionHandler, Animation** currentAnimation,ID3D11Buffer** currentAnimationBuffer,Graphics* graphics, DirectX::Keyboard* keyboard);
private:
	enum class VelocityMode
	{
		Add,
		Set
	};
	DirectX::Keyboard* keyboard;
	Graphics* graphics;

	Vector3 curVelocity;
	Vector3 previousTranslation;
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
	void AddVelocity(Vector3 newVelocity, VelocityMode velocityMode); 
	void ApplyGravity(); 
	void ClampVelocity(); 
	void SwitchFacingDir(); 
	void GetInput(Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer);

};