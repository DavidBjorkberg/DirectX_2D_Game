#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(Vector3 position, float width, float height, CollisionHandler* collisionHandler
	, Animation** currentAnimation, ID3D11Buffer** currentAnimationBuffer, Graphics* graphics, DirectX::Keyboard* keyboard)
{
	this->position = position;
	this->collisionHandler = collisionHandler;
	this->graphics = graphics;
	graphics->CreateConstantBuffer(&moveBuffer, sizeof(Matrix));
	graphics->CreateConstantBuffer(&facingDirBuffer, 16);
	graphics->MapToBuffer(facingDirBuffer, &facingRight, sizeof(bool));
	this->keyboard = keyboard;
	collider = new BoxCollider(position + Vector3(0.4f, 0.1f, 0), width - 1.4f, height - 0.8f, 0);
	attackCollider = new BoxCollider(position + Vector3(0.4f, 0.1f, 0) + Vector3(attackRange / 2, attackHeight / 2, 0), attackRange, attackHeight, -1);

	collisionHandler->AddCollider(collider);
}
void PlayerMovement::Update(float deltaTime, Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer)
{
	this->deltaTime = deltaTime;
	ApplyGravity();

	GetInput(currentAnimation, currentAnimationBuffer);
	ClampVelocity();

	CheckNextFrameCollision();
	Move();
	ApplyGravity();
}
void PlayerMovement::Move()
{
	Vector3 finalVelocity = (curVelocity)*deltaTime;
	if (!canMove)
	{
		finalVelocity.x = 0;
	}
	if (collisionHandler->isCollidingAfterMove(collider, finalVelocity) == nullptr)
	{
		previousTranslation += finalVelocity;
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		graphics->MoveCamera(finalVelocity.x, finalVelocity.y);
		position += finalVelocity;
		collider->Move(finalVelocity);
		attackCollider->Move(finalVelocity);
		graphics->MapToBuffer(moveBuffer, &moveMatrix, sizeof(Matrix));
	}
}
void PlayerMovement::Jump()
{
	AddVelocity(Vector3(curVelocity.x, jumpForce, 0), VelocityMode::Set);
}
void PlayerMovement::CheckNextFrameCollision()
{
	BoxCollider* collidedWith = collisionHandler->isCollidingAfterMove(collider, curVelocity * deltaTime);
	if (collidedWith != nullptr)
	{
		if (!collider->IsCollidingAfterMove(collidedWith, Vector3(curVelocity.x, 0, 0) * deltaTime))
		{
			curVelocity.y = 0;
		}
		else if (!collider->IsCollidingAfterMove(collidedWith, Vector3(0, curVelocity.y, 0) * deltaTime))
		{
			curVelocity.x = 0;
		}
		else
		{
			curVelocity = Vector3::Zero;
		}
	}
}

void PlayerMovement::AddVelocity(Vector3 addVelocity, VelocityMode velocityMode)
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
		AddVelocity(Vector3::Down * gravity * 2 * deltaTime, VelocityMode::Add);
	}
	else if (curVelocity.y > 0 && !keyboard->GetState().Space)
	{
		AddVelocity(Vector3::Down * gravity * 2 * deltaTime, VelocityMode::Add);
	}
	//Regular gravity 
	AddVelocity(Vector3::Down * gravity * deltaTime, VelocityMode::Add);
}

void PlayerMovement::GetInput(Animation** currentAnimation, ID3D11Buffer* currentAnimationBuffer)
{
	DirectX::Keyboard::State kb = keyboard->GetState();

	if (kb.A)
	{
		if (facingRight)
		{
			SwitchFacingDir();
		}
		AddVelocity(Vector3::Left * acceleration * deltaTime, VelocityMode::Add);
	}
	else if (kb.D)
	{
		if (!facingRight)
		{
			SwitchFacingDir();
		}

		AddVelocity(Vector3::Right * acceleration * deltaTime, VelocityMode::Add);
	}
	if (IsGrounded())
	{
		if (!kb.A && !kb.D)
		{
			if (curVelocity.x > 0)
			{
				AddVelocity(Vector3::Left * acceleration * deltaTime, VelocityMode::Add);
				if (curVelocity.x < 0)
				{
					curVelocity.x = 0;
				}
			}
			else
			{
				AddVelocity(Vector3::Right * acceleration * deltaTime, VelocityMode::Add);
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
	return collisionHandler->isCollidingAfterMove(collider, Vector3::Down * 0.1f) && curVelocity.y <= 0;
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
	if (facingRight)
	{
		previousTranslation += Vector3(-1, 0, 0);
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		collider->Move(Vector3(-0.4f, 0, 0));
		attackCollider->Move(Vector3(-(1 + (attackRange / 2)), 0, 0));
	}
	else
	{
		previousTranslation += Vector3(1, 0, 0);
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		collider->Move(Vector3(0.4f, 0, 0));
		attackCollider->Move(Vector3(1 + (attackRange / 2), 0, 0));
	}
	graphics->MapToBuffer(moveBuffer, &moveMatrix, sizeof(Matrix));
	facingRight = !facingRight;
	graphics->MapToBuffer(facingDirBuffer, &facingRight, sizeof(bool));
}

