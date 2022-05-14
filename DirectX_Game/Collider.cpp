#include "Collider.h"
#include "CollisionHandler.h"
#include "Physics.h"
bool Collider::IsColliding(Collider* other)
{
	return false;
}

bool Collider::IsCollidingAfterMove(Collider* other, Vector2 moveVec)
{
	return false;
}

void Collider::Move(Vector2 moveVec)
{
}

void Collider::Initialize(void* owner)
{
	Component::Initialize(owner);
	CollisionHandler::AddCollider(this);
}

Collider::Collider(Physics::Layer layer)
{
	this->layer = layer;
}

Collider::Collider()
{
}

