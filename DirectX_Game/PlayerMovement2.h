#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"
class PlayerMovement2 : public Component
{
public:
	PlayerMovement2();
	void Initialize(void* owner)override;
	void Update(float deltaTime)override;
	void HandleInput(float deltaTime);
private:
	Transform* transform;
	Rigidbody* rigidbody;
	float movementSpeed = 5;
};