#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(Vector3 bottomLeftPos, float width, float height, int unitIndex)
{
	this->bottomLeftPos = bottomLeftPos;
	this->width = width;
	this->height = height;
	this->unitIndex = unitIndex;
}

bool BoxCollider::IsColliding(BoxCollider* other)
{
	bool xCollision = this->bottomLeftPos.x < other->bottomLeftPos.x + other->width
					&& this->bottomLeftPos.x + this->width > other->bottomLeftPos.x;
	bool yCollision = this->bottomLeftPos.y < other->bottomLeftPos.y + other->height
					&& this->bottomLeftPos.y + this->height > other->bottomLeftPos.y;
	return xCollision && yCollision;
}

bool BoxCollider::IsCollidingAfterMove(BoxCollider* other, Vector3 moveVec)
{
	Vector3 nextFramePos = bottomLeftPos + moveVec;
	bool xCollision = nextFramePos.x < other->bottomLeftPos.x + other->width
		&& nextFramePos.x + this->width > other->bottomLeftPos.x;
	bool yCollision = nextFramePos.y < other->bottomLeftPos.y + other->height
		&& nextFramePos.y + this->height > other->bottomLeftPos.y;

	return xCollision && yCollision;
}

void BoxCollider::Move(Vector3 moveVec)
{
	bottomLeftPos += moveVec;
}
