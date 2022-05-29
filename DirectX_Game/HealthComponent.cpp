#include "HealthComponent.h"

HealthComponent::HealthComponent()
{
}

void HealthComponent::Initialize(void* owner)
{
	Component::Initialize(owner);
}

void HealthComponent::TakeDamage(int amount)
{
	this->health -= amount;
	tookDamageTrigger = true;
}

HealthComponent::HealthComponent(int maxHealth)
{
	this->maxHealth = maxHealth;
	this->health = maxHealth;
}
