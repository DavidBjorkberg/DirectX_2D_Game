#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
public:
	bool IsColliding(Collider* other)override;
	bool IsCollidingAfterMove(Collider* other, Vector2 moveVec)override;
	void Move(Vector2 moveVec)override;
	BoxCollider();
	BoxCollider(Vector2 pos, float width, float height, Physics::Layer layer);
};