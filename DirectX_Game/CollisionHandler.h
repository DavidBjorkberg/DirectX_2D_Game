#pragma once
#include"Collider.h"
#include<vector>
static class CollisionHandler
{
public:
	static void AddCollider(Collider* collider);
	static void RemoveCollider(Collider* collider);
	static std::vector<Collider*> GetCollisions(Collider* collider);
	static Collider* isCollidingAfterMove(Collider* collider, Vector2 moveVec);
	static bool IsPointCollidingWithLevel(Vector3 point);
	static std::vector<Collider*> GetAllCollidersInLevel();
	CollisionHandler();
private:
	static std::vector<Collider*> colliders;
};