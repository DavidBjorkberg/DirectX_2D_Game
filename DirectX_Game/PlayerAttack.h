#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Transform.h"
#include "PlayerMovement2.h"
using namespace DirectX::SimpleMath;
class PlayerAttack : public Component
{
public:
	virtual void Initialize(void* owner) override;
	virtual void Update(float deltaTime) override;
	PlayerAttack();
private:
	void Attack();
	Transform* transform;
	PlayerMovement2* playerMovement;
	int damage = 1;
};