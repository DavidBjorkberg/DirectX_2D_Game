#include "CollisionHandler.h"

void CollisionHandler::AddCollider(BoxCollider* collider)
{
	this->colliders.push_back(collider);
}

bool CollisionHandler::isColliding(BoxCollider* collider)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (collider->IsColliding(colliders[i]))
		{
			return true;
		}
	}
	return false;
}

BoxCollider* CollisionHandler::isCollidingNextFrame(BoxCollider* collider, Vector3 moveVec)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->bottomLeftPos != collider->bottomLeftPos && collider->IsCollidingNextFrame(colliders[i],moveVec))
		{
			return colliders[i];
		}
	}
	return nullptr;
}

CollisionHandler::CollisionHandler()
{
}
