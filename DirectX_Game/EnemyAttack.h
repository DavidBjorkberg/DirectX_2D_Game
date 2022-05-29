#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Transform.h"
#include "EnemyMovement.h"

using namespace DirectX::SimpleMath;
class EnemyAttack : public Component
{
public:
	virtual void Initialize(void* owner) override;
	virtual void Update(float deltaTime) override;
	EnemyAttack();
	bool attackTrigger;
private:
	Transform* transform;
	EnemyMovement* enemyMovement;
	int damage = 1;
};