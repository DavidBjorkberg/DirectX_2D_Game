#include "HealthComponent.h"

void HealthComponent::Initialize(void* owner)
{
	Component::Initialize(owner);
}

void HealthComponent::TakeDamage(int amount)
{
	this->Health -= amount;
	TookDamageTrigger = true;
}

HealthComponent::HealthComponent(int maxHealth)
{
	this->MaxHealth = maxHealth;
	this->Health = maxHealth;
}
