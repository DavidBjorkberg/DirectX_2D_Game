#pragma once
#include"BoxCollider.h"
#include<vector>
class CollisionHandler
{
public:
	void AddCollider(BoxCollider* collider);
	CollisionHandler();
private:
	std::vector<BoxCollider*> colliders;
};