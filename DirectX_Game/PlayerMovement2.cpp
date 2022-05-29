#include "PlayerMovement2.h"
#include <d3d11.h>
#include "Game.h"
#include "Rigidbody.h"
#include "Input.h"
#include "Raycast.h"
PlayerMovement2::PlayerMovement2()
{
}

void PlayerMovement2::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->transform = static_cast<Entity*>(owner)->GetComponent<Transform>();
	this->rigidbody = static_cast<Entity*>(owner)->GetComponent<Rigidbody>();
	this->spriteRenderer = static_cast<Entity*>(owner)->GetComponent<SpriteRenderer>();
}

void PlayerMovement2::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void PlayerMovement2::HandleInput(float deltaTime)
{
	Vector2 moveDirection = Vector2::Zero;
	running = false;
	if (Input::KeyDown(DirectX::Keyboard::A))
	{
		moveDirection -= Vector2(1, 0);
		facingDir = Vector2(-1, 0);
		spriteRenderer->SetFlipX(true);
		running = true;
	}
	if (Input::KeyDown(DirectX::Keyboard::D))
	{
		moveDirection += Vector2(1, 0);
		facingDir = Vector2(1, 0);
		spriteRenderer->SetFlipX(false);
		running = true;
	}
	if (moveDirection != Vector2::Zero)
	{
		this->transform->TryMove(moveDirection * movementSpeed * deltaTime, false);
	}
	if (Input::KeyPressed(DirectX::Keyboard::Space) && IsGrounded())
	{
		rigidbody->AddVelocity(Vector2(0, 0.01f), Rigidbody::VelocityMode::Set);
		jumpAnimTrigger = true;
	}
}

bool PlayerMovement2::IsGrounded()
{
	return RaycastUtility::Raycast(this->transform->GetPosition(), Vector2(0, -1), 1, static_cast<Entity*>(owner)->GetComponent<Collider>()->layer.CollisionMask);
}
