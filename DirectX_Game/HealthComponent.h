#pragma once
#include "Component.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;
class HealthComponent : public Component
{
public:
	virtual void Initialize(void* owner) override;
	void TakeDamage(int amount);
	HealthComponent(int maxHealth);
	bool TookDamageTrigger;
private:
	int Health;
	int MaxHealth;
};