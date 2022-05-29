#pragma once
#include "Component.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;
class HealthComponent : public Component
{
public:
	HealthComponent();
	virtual void Initialize(void* owner) override;
	void TakeDamage(int amount);
	HealthComponent(int maxHealth);
	bool tookDamageTrigger;
private:
	int health;
	int maxHealth;
};