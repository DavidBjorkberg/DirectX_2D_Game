#pragma once
#include"BoxCollider.h"
#include<vector>
class CollisionHandler
{
public:
	void AddCollider(BoxCollider* collider);
	bool isColliding(BoxCollider* collider);
	std::vector<BoxCollider*> GetCollisions(BoxCollider* collider);
	BoxCollider* isCollidingAfterMove(BoxCollider* collider, Vector3 moveVec);
	CollisionHandler();
private:
	std::vector<BoxCollider*> colliders;
};