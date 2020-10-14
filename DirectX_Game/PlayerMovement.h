#pragma once
#include"SimpleMath.h"
#include"Animation.h"
#include"CollisionHandler.h"
#include"Keyboard.h"

using namespace DirectX::SimpleMath;
class PlayerMovement
{
public:
	Animation* jumpAnimation;//
	Animation* idleAnimation;//
	Animation* runAnimation;// 
	ID3D11Buffer* moveBuffer;//
	ID3D11Buffer* facingDirBuffer;//

	void Update(float deltaTime, Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer);
	bool IsGrounded(); ///
	PlayerMovement(Vector3 position, float width, float height,CollisionHandler* collisionHandler, Animation** currentAnimation,ID3D11Buffer** currentAnimationBuffer,Graphics* graphics, DirectX::Keyboard* keyboard);
private:
	enum class VelocityMode
	{
		Add,
		Set
	};
	DirectX::Keyboard* keyboard;
	Graphics* graphics;
	CollisionHandler* collisionHandler;// 

	Vector3 curVelocity;
	Vector3 previousTranslation;
	Matrix moveMatrix = Matrix::Identity;
	BoxCollider* collider;

	bool canJump = true; //
	bool facingRight = true; //
	float gravity = 6; //

	float jumpForce = 9; //
	float maxXVelocity = 5; //
	float acceleration = 10; //
	float deltaTime;

	void Move(); //
	void Jump(Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer); //
	void CheckNextFrameCollision(); //
	void AddVelocity(Vector3 newVelocity, VelocityMode velocityMode); //
	void ApplyGravity(); //
	void ClampVelocity(); // 
	void SwitchFacingDir(); //
	void GetInput(Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer);

};