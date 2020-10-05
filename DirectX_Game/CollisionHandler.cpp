#include "CollisionHandler.h"

void CollisionHandler::AddCollider(BoxCollider* collider)
{
	this->colliders.push_back(collider);
}

CollisionHandler::CollisionHandler()
{
}
