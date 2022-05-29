#pragma once
#include "Component.h"
#include <SimpleMath.h>
#include "Physics.h"
using namespace DirectX::SimpleMath;
class Collider : public Component
{
public:
	Collider(Physics::Layer layer);
	Collider();
	virtual bool IsColliding(Collider* other);
	virtual bool IsCollidingAfterMove(Collider* other, Vector2 moveVec);
	virtual void Move(Vector2 moveVec);
	virtual void Initialize(void* owner)override;
	Vector2 bottomLeftPos;
	float width;
	float height;
	Physics::Layer layer;
};