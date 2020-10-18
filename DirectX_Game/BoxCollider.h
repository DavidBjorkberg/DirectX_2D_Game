#pragma once
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
class BoxCollider
{
public:
	Vector3 bottomLeftPos;
	float width;
	float height;
	int unitIndex; // -1 = non-unit, 0 = player 1+ = enemy index

	bool IsColliding(BoxCollider* other);
	bool IsCollidingAfterMove(BoxCollider* other,Vector3 moveVec);
	void Move(Vector3 moveVec);
	BoxCollider();
	BoxCollider(Vector3 pos, float width, float height,int unitIndex);
private:

};