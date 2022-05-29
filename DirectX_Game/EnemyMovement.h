#pragma once
#include "Component.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
class EnemyMovement : public Component
{
public:
	EnemyMovement();
	void Initialize(void* owner)override;
	void Update(float deltaTime)override;
	Vector2 walkingDirection = Vector2(1, 0);
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	float movementSpeed = 5;
};