#pragma once
#include "Component.h"
#include "Transform.h"
class Rigidbody : public Component
{
public:
	enum class VelocityMode
	{
		Add,
		Set
	};
	virtual void Update(float deltaTime)override;
	virtual void LateUpdate(float deltaTime)override;
	virtual void Initialize(void* owner)override;
	void SetGravity(float newGravity);
	void AddVelocity(Vector2 newVelocity, VelocityMode velocityMode);
	Vector2 GetVelocity();
private:

	void ApplyGravity(float deltaTime);
	float gravity =0.025f;
	Vector2 curVelocity;
	Transform* transform;
};