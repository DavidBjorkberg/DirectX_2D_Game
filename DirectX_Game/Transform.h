#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "CollisionHandler.h"

using namespace DirectX::SimpleMath;
class Transform : public Component
{
public:
	Transform();
	Transform(Vector2 position);
	Vector2 GetPosition();
	void SetPosition(Vector2 newPos);
	Vector2 GetRotation();
	void SetRotation(Vector2 newRot);
	bool TryMove(Vector2 moveVec, bool useAsPosition);
	virtual void Initialize(void* owner) override;
private:
	Vector2 position;
	Vector2 rotation;
};