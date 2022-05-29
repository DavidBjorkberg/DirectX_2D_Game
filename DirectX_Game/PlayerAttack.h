#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Transform.h"
#include "PlayerMovement.h"
using namespace DirectX::SimpleMath;
class PlayerAttack : public Component
{
public:
	PlayerAttack();
	virtual void Initialize(void* owner) override;
	virtual void Update(float deltaTime) override;
private:
	void Attack();
	Transform* transform;
	PlayerMovement* playerMovement;
	int damage = 1;
};