#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
class PlayerMovement2 : public Component
{
public:
	PlayerMovement2();
	void Initialize(void* owner)override;
	void Update(float deltaTime)override;
	void HandleInput(float deltaTime);
	bool IsGrounded();
	bool running; 
	bool jumpAnimTrigger;
private:
	Transform* transform;
	Rigidbody* rigidbody;
	SpriteRenderer* spriteRenderer;
	float movementSpeed = 5;
};