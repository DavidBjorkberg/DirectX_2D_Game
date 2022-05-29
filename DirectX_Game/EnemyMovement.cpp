#include "EnemyMovement.h"
#include "Entity.h"
#include "Physics.h"
#include "Raycast.h"
EnemyMovement::EnemyMovement()
{
}

void EnemyMovement::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->transform = static_cast<Entity*>(owner)->GetComponent<Transform>();
	this->spriteRenderer = static_cast<Entity*>(owner)->GetComponent<SpriteRenderer>();
}

void EnemyMovement::Update(float deltaTime)
{
	if (RaycastUtility::Raycast(transform->GetPosition(), walkingDirection, 1, static_cast<Entity*>(owner)->GetComponent<Collider>()->layer.CollisionMask) ||
		!RaycastUtility::Raycast(transform->GetPosition() + walkingDirection, Vector2(0, -1), 1, static_cast<Entity*>(owner)->GetComponent<Collider>()->layer.CollisionMask))
	{
		walkingDirection *= -1;
		spriteRenderer->SetFlipX(!spriteRenderer->GetFlipX());
	}
	this->transform->TryMove(walkingDirection * movementSpeed * deltaTime, false);
}
