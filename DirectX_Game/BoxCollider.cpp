#include "BoxCollider.h"
#include"CollisionHandler.h"
BoxCollider::BoxCollider(Vector2 bottomLeftPos, float width, float height, Physics::Layer layer)
	: Collider(layer)
{
	this->bottomLeftPos = bottomLeftPos;
	this->width = width;
	this->height = height;
}

bool BoxCollider::IsColliding(Collider* other)
{
	bool layerCollide = this->layer.CategoryMask & other->layer.CollisionMask;
	bool xCollision = this->bottomLeftPos.x < other->bottomLeftPos.x + other->width
		&& this->bottomLeftPos.x + this->width > other->bottomLeftPos.x;
	bool yCollision = this->bottomLeftPos.y < other->bottomLeftPos.y + other->height
		&& this->bottomLeftPos.y + this->height > other->bottomLeftPos.y;
	return xCollision && yCollision && layerCollide;
}

bool BoxCollider::IsCollidingAfterMove(Collider* other, Vector2 moveVec)
{
	bool layerCollide = this->layer.CategoryMask & other->layer.CollisionMask;
	Vector2 posAfterMove = this->bottomLeftPos + moveVec;
	bool xCollision = posAfterMove.x < other->bottomLeftPos.x + other->width
		&& posAfterMove.x + this->width > other->bottomLeftPos.x;
	bool yCollision = posAfterMove.y < other->bottomLeftPos.y + other->height
		&& posAfterMove.y + this->height > other->bottomLeftPos.y;
	return xCollision && yCollision && layerCollide;
}

void BoxCollider::Move(Vector2 moveVec)
{
	bottomLeftPos += moveVec;
}

BoxCollider::BoxCollider()
{

}

