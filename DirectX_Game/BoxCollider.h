#pragma once
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
class BoxCollider
{
public:

	BoxCollider();
	BoxCollider(Vector3 pos, float width, float height);
	bool IsColliding(BoxCollider* other);
	bool IsCollidingAfterMove(BoxCollider* other,Vector3 moveVec);
	void Move(Vector3 moveVec);
	Vector3 bottomLeftPos;
private:
	float width;
	float height;

};