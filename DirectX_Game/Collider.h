#pragma once
#include "Component.h"
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
class Collider : public Component
{
public:
	Vector2 bottomLeftPos;
	float width;
	float height;

	virtual bool IsColliding(Collider* other);
	virtual bool IsCollidingAfterMove(Collider* other, Vector2 moveVec);
	virtual void Move(Vector2 moveVec);
	virtual void Initialize(void* owner)override;
	Collider();
};