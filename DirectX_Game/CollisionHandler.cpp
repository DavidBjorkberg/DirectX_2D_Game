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

std::vector<BoxCollider*> CollisionHandler::GetCollisions(BoxCollider* collider)
{
	std::vector<BoxCollider*> hits;
	for (int i = 0; i < colliders.size(); i++)
	{
		if (collider->IsColliding(colliders[i]))
		{
			hits.push_back(colliders[i]);
		}
	}
	return hits;
}

BoxCollider* CollisionHandler::isCollidingAfterMove(BoxCollider* collider, Vector3 moveVec)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->bottomLeftPos != collider->bottomLeftPos && collider->IsCollidingAfterMove(colliders[i],moveVec))
		{
			return colliders[i];
		}
	}
	return nullptr;
}

bool CollisionHandler::IsPointCollidingWithLevel(Vector3 point)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->unitIndex != -1)
		{
			continue;
		}
		if (point.x > colliders[i]->bottomLeftPos.x && point.x < colliders[i]->bottomLeftPos.x + colliders[i]->width
			&& point.y > colliders[i]->bottomLeftPos.y && point.y < colliders[i]->bottomLeftPos.y + colliders[i]->height)
		{
			return true;
		}
	}
	return false;
}

CollisionHandler::CollisionHandler()
{
}
