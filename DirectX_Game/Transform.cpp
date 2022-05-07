#include "Transform.h"
#include"BoxCollider.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
DirectX::SimpleMath::Vector2 Transform::GetPosition()
{
	return this->position;
}

Transform::Transform(Vector2 position)
{
	this->position = position; //Set position with this value is called in Initialize()
}
void Transform::SetPosition(DirectX::SimpleMath::Vector2 newPos)
{
	DirectX::SimpleMath::Matrix moveMatrix = Matrix::CreateTranslation(Vector3(newPos.x, newPos.y, 0));
	if (SpriteRenderer* sr = static_cast<Entity*>(owner)->GetComponent<SpriteRenderer>())
	{
		sr->UpdatePositionBuffer(&moveMatrix);
	}
	this->position = newPos;
}

Vector2 Transform::GetRotation()
{
	return Vector2();
}

void Transform::SetRotation(Vector2 newRot)
{
}

bool Transform::TryMove(Vector2 moveVec, bool useAsPosition) //TODO: MovementComponent?
{
	std::vector<BoxCollider*>* colliders = static_cast<Entity*>(owner)->GetAllComponentsOfType<BoxCollider>();
	for (BoxCollider* collider : *colliders)
	{
		if (CollisionHandler::isCollidingAfterMove(collider, useAsPosition ? moveVec - this->position : moveVec))
		{
			return false;
		}
	}
	SetPosition(useAsPosition ? moveVec : this->position + moveVec);
	for (BoxCollider* collider : *colliders)
	{
		collider->Move(moveVec); //TODO: Handle useAsPosition
	}
	return true;
}

void Transform::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->SetPosition(this->position);
}
