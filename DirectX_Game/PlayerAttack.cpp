#include "PlayerAttack.h"
#include "Input.h"
#include "Raycast.h"
#include "Entity.h"
#include "HealthComponent.h"
void PlayerAttack::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->transform = static_cast<Entity*>(owner)->GetComponent<Transform>();
	this->playerMovement = static_cast<Entity*>(owner)->GetComponent<PlayerMovement>();

}

void PlayerAttack::Update(float deltaTime)
{
	if (Input::KeyPressed(DirectX::Keyboard::Keys::F))
	{
		Attack();
	}
}

PlayerAttack::PlayerAttack()
{

}

void PlayerAttack::Attack()
{
	if (Entity* hitEnemy = RaycastUtility::Raycast(transform->GetPosition(), playerMovement->facingDir, 1.2, ~static_cast<Entity*>(owner)->GetComponent<Collider>()->layer.CollisionMask))
	{
		hitEnemy->GetComponent<HealthComponent>()->TakeDamage(damage);
	}
}
