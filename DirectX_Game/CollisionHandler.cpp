#include "CollisionHandler.h"

std::vector<Collider*> CollisionHandler::colliders;

void CollisionHandler::AddCollider(Collider* collider)
{
	colliders.push_back(collider);
}

void CollisionHandler::RemoveCollider(Collider* collider)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (collider == colliders[i])
		{
			colliders.erase(colliders.begin() + i);
			delete collider;
			break;
		}
	}
}


Collider* CollisionHandler::isCollidingAfterMove(Collider* collider, Vector2 moveVec)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->bottomLeftPos != collider->bottomLeftPos && collider->IsCollidingAfterMove(colliders[i], moveVec))
		{
			return colliders[i];
		}
	}
	return nullptr;
}


std::vector<Collider*> CollisionHandler::GetAllCollidersInLevel()
{
	return colliders;
}

CollisionHandler::CollisionHandler()
{
}
