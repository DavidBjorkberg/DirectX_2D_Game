#pragma once
#include"BoxCollider.h"
#include<vector>
class CollisionHandler
{
public:
	void AddCollider(BoxCollider* collider);
	void RemoveCollider(BoxCollider* collider);
	bool isColliding(BoxCollider* collider);
	std::vector<BoxCollider*> GetCollisions(BoxCollider* collider);
	BoxCollider* isCollidingAfterMove(BoxCollider* collider, Vector3 moveVec);
	bool IsPointCollidingWithLevel(Vector3 point);
	CollisionHandler();
private:
	std::vector<BoxCollider*> colliders;
};