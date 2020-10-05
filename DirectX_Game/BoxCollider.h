#pragma once
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
class BoxCollider
{
public:

	BoxCollider();
	BoxCollider(Vector3 pos, float width, float height);
	bool IsColliding(BoxCollider other);
private:
	Vector3 bottomLeftPos;
	float width;
	float height;

};