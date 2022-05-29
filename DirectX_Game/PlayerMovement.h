#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
class PlayerMovement : public Component
{
public:
	PlayerMovement();
	void Initialize(void* owner)override;
	void Update(float deltaTime)override;
	void HandleInput(float deltaTime);
	bool IsGrounded();
	bool running; 
	bool jumpAnimTrigger;
	Vector2 facingDir;
private:
	Transform* transform;
	Rigidbody* rigidbody;
	SpriteRenderer* spriteRenderer;
	float movementSpeed = 5;
};