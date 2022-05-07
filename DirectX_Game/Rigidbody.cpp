#include "Rigidbody.h"
#include "Entity.h"

void Rigidbody::Update(float deltaTime)
{
	ApplyGravity(deltaTime);
	this->transform->TryMove(curVelocity, false);
}

void Rigidbody::LateUpdate(float deltaTime)
{
	ApplyGravity(deltaTime);
}

void Rigidbody::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->transform = static_cast<Entity*>(owner)->GetComponent<Transform>();
}

void Rigidbody::SetGravity(float newGravity)
{
	this->gravity = newGravity;
}


void Rigidbody::ApplyGravity(float deltaTime)
{
	AddVelocity(Vector2(0, -1) * gravity * deltaTime, VelocityMode::Add);
}

void Rigidbody::AddVelocity(Vector2 newVelocity, VelocityMode velocityMode)
{
	switch (velocityMode)
	{
	case Rigidbody::VelocityMode::Add:
		curVelocity += newVelocity;
		break;
	case Rigidbody::VelocityMode::Set:
		curVelocity = newVelocity;
		break;
	default:
		break;
	}
}
