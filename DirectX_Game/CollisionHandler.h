#pragma once
#include"Collider.h"
#include<vector>
static class CollisionHandler
{
public:
	CollisionHandler();
	static void AddCollider(Collider* collider);
	static void RemoveCollider(Collider* collider);
	static Collider* isCollidingAfterMove(Collider* collider, Vector2 moveVec);
	static std::vector<Collider*> GetAllCollidersInLevel();
private:
	static std::vector<Collider*> colliders;
};