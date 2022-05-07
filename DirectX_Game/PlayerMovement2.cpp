#include "PlayerMovement2.h"
#include <d3d11.h>
#include "Game.h"
#include "Rigidbody.h"
#include "Input.h"

PlayerMovement2::PlayerMovement2()
{
}

void PlayerMovement2::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->transform = static_cast<Entity*>(owner)->GetComponent<Transform>();
	this->rigidbody = static_cast<Entity*>(owner)->GetComponent<Rigidbody>();
}

void PlayerMovement2::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void PlayerMovement2::HandleInput(float deltaTime)
{
	Vector2 moveDirection = Vector2::Zero;
	if (Input::KeyDown(DirectX::Keyboard::A))
	{
		moveDirection -= Vector2(1, 0);
	}
	if (Input::KeyDown(DirectX::Keyboard::D))
	{
		moveDirection += Vector2(1, 0);
	}
	if (moveDirection != Vector2::Zero)
	{
		this->transform->TryMove(moveDirection * movementSpeed * deltaTime, false);
	}
	if (Input::KeyPressed(DirectX::Keyboard::Space))
	{
		rigidbody->AddVelocity(Vector2(0, 0.005f), Rigidbody::VelocityMode::Set);
	}
}
