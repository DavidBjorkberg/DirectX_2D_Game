#include "PlayerMovement.h"
#include "Transform.h"
#include "Entity.h"
PlayerMovement::PlayerMovement(Vector2 position, float width, float height, CollisionHandler* collisionHandler
	, Graphics* graphics, DirectX::Keyboard* keyboard)
{
	this->position = position;
	this->collisionHandler = collisionHandler;
	this->graphics = graphics;
	this->keyboard = keyboard;
	//attackCollider = new BoxCollider(position + Vector2(0.4f, 0.1f) + Vector2(attackRange / 2, attackHeight / 2), attackRange, attackHeight, -1);

}
void PlayerMovement::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	ApplyGravity();

	GetInput();
	ClampVelocity();

	CheckNextFrameCollision();
	Move();
	ApplyGravity();
}
void PlayerMovement::Move()
{
	Vector2 finalVelocity = (curVelocity)*deltaTime;
	if (!canMove)
	{
		finalVelocity.x = 0;
	}
	//static_cast<GameObject*>(owner)->GetComponent<Transform>()->TryMove(finalVelocity, false);
}
void PlayerMovement::Jump()
{
	AddVelocity(Vector2(curVelocity.x, jumpForce), VelocityMode::Set);
}
void PlayerMovement::CheckNextFrameCollision()
{
	
}

void PlayerMovement::AddVelocity(Vector2 addVelocity, VelocityMode velocityMode)
{
	if (velocityMode == VelocityMode::Add)
	{
		curVelocity += addVelocity;
	}
	else if (velocityMode == VelocityMode::Set)
	{
		curVelocity = addVelocity;
	}
}
void PlayerMovement::ApplyGravity()
{
	//For high jump
	if (curVelocity.y < 0)
	{
		AddVelocity(Vector2(0, -1) * gravity * 2 * deltaTime, VelocityMode::Add);
	}
	else if (curVelocity.y > 0 && !keyboard->GetState().Space)
	{
		AddVelocity(Vector2(0, -1) * gravity * 2 * deltaTime, VelocityMode::Add);
	}
	//Regular gravity 
	AddVelocity(Vector2(0, -1) * gravity * deltaTime, VelocityMode::Add);
}

void PlayerMovement::GetInput()
{
	DirectX::Keyboard::State kb = keyboard->GetState();

	if (kb.A)
	{
		if (facingRight)
		{
			SwitchFacingDir();
		}
		AddVelocity(Vector2(-1, 0) * acceleration * deltaTime, VelocityMode::Add);
	}
	else if (kb.D)
	{
		if (!facingRight)
		{
			SwitchFacingDir();
		}

		AddVelocity(Vector2(1, 0) * acceleration * deltaTime, VelocityMode::Add);
	}
	if (IsGrounded())
	{
		if (!kb.A && !kb.D)
		{
			if (curVelocity.x > 0)
			{
				AddVelocity(Vector2(-1, 0) * acceleration * deltaTime, VelocityMode::Add);
				if (curVelocity.x < 0)
				{
					curVelocity.x = 0;
				}
			}
			else
			{
				AddVelocity(Vector2(1, 0) * acceleration * deltaTime, VelocityMode::Add);
				if (curVelocity.x > 0)
				{
					curVelocity.x = 0;
				}
			}
		}
		if (kb.IsKeyDown(DirectX::Keyboard::Keys::Space) && canJump)
		{
			Jump();
			canJump = false;
		}
	}
	if (kb.IsKeyUp(DirectX::Keyboard::Keys::Space))
	{
		canJump = true;
	}
}

bool PlayerMovement::IsGrounded()
{
	return false;
}

void PlayerMovement::ClampVelocity()
{
	if (abs(curVelocity.x) > maxXVelocity)
	{
		if (curVelocity.x > 0)
		{
			curVelocity.x = maxXVelocity;
		}
		else
		{
			curVelocity.x = -maxXVelocity;
		}
	}
}
void PlayerMovement::SwitchFacingDir()
{
	//TODO:
	//if (facingRight)
	//{
	//	previousTranslation += Vector3(-1, 0, 0);
	//	moveMatrix = Matrix::CreateTranslation(previousTranslation);
	//	collider->Move(Vector3(-0.4f, 0, 0));
	//	attackCollider->Move(Vector3(-(1 + (attackRange / 2)), 0, 0));
	//}
	//else
	//{
	//	previousTranslation += Vector3(1, 0, 0);
	//	moveMatrix = Matrix::CreateTranslation(previousTranslation);
	//	collider->Move(Vector3(0.4f, 0, 0));
	//	attackCollider->Move(Vector3(1 + (attackRange / 2), 0, 0));
	//}
	//graphics->MapToBuffer(moveBuffer, &moveMatrix, sizeof(Matrix));
	//facingRight = !facingRight;
	//graphics->MapToBuffer(facingDirBuffer, &facingRight, sizeof(bool));
}

