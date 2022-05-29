#include "EnemyAttack.h"
#include "Raycast.h"
#include "HealthComponent.h"
void EnemyAttack::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->enemyMovement = static_cast<Entity*>(owner)->GetComponent<EnemyMovement>();

}

void EnemyAttack::Update(float deltaTime)
{
	if (Entity* hitPlayer = RaycastUtility::Raycast(transform->GetPosition(), enemyMovement->walkingDirection, 1, static_cast<Entity*>(owner)->GetComponent<Collider>()->layer.CollisionMask))
	{
		attackTrigger = true;
		hitPlayer->GetComponent<HealthComponent>()->TakeDamage(damage);
	}
}

EnemyAttack::EnemyAttack()
{
}
