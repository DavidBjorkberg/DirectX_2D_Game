#include "Enemy.h"

void Enemy::Update(Vector3 playerPos, float deltaTime, bool isPlayerAlive)
{
	this->damagedPlayer = false;
	this->deltaTime = deltaTime;
	ApplyGravity();
	CheckNextFrameCollision();
	UpdateAnimation();
	if (isPlayerAlive)
	{
		ObservePlayer(playerPos);

	}
	Move();
	ApplyGravity();
}

void Enemy::TakeDamage()
{
	currentAnimation = hitAnimation->Play(currentAnimationBuffer, currentAnimation);
	isWalking = false;
	health--;
}

Enemy::Enemy()
{
}

Enemy::Enemy(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler, int enemyIndex)
{
	this->position = pos;
	this->graphics = graphics;
	this->collisionHandler = collisionHandler;

	texture.Initialize(graphics->device, graphics->deviceContext, "Textures/Small_Enemy_SpriteSheet.png");
	graphics->CreateConstantBuffer(&currentAnimationBuffer, 16);
	graphics->CreateConstantBuffer(&moveBuffer, sizeof(Matrix));
	graphics->CreateConstantBuffer(&facingDirBuffer, 16);
	attackCollider = new BoxCollider(position + Vector3(0.4f, 0.1f, 0) + Vector3(attackRange / 2, attackHeight / 2, 0), attackRange, attackHeight, -1);
	collider = new BoxCollider(position + Vector3(0.4f, 0.1f, 0), modelWidth, modelHeight, enemyIndex);
	collisionHandler->AddCollider(collider);
	graphics->MapToBuffer(facingDirBuffer, &facingRight, sizeof(bool));
	graphics->MapToBuffer(moveBuffer, &moveMatrix, sizeof(Matrix));
	runAnimation = new Animation(graphics, Animation::AnimationType::Run);
	attackAnimation = new Animation(graphics, Animation::AnimationType::Attack, false);
	hitAnimation = new Animation(graphics, Animation::AnimationType::Hit, false, 20);

	currentAnimation = runAnimation->Play(currentAnimationBuffer, currentAnimation);
	curVelocity.x = 1;

	InitializeShaders();
	CreateDrawable();
}
void Enemy::UpdateAnimation()
{
	switch (currentAnimation->animationType)
	{
	case Animation::AnimationType::Hit:
		if (!currentAnimation->isPlaying)
		{
			if (health <= 0)
			{
				isToBeRemoved = true;
			}
			else
			{
				isWalking = true;
				currentAnimation = runAnimation->Play(currentAnimationBuffer, currentAnimation);
			}
		}
		break;
	case Animation::AnimationType::Attack:
		if (!currentAnimation->isPlaying)
		{
			isWalking = true;
			currentAnimation = runAnimation->Play(currentAnimationBuffer, currentAnimation);
		}
		break;
	default:
		break;
	}
	currentAnimation->Update(deltaTime, currentAnimationBuffer);
}
void Enemy::SwitchWalkingDir()
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
		attackCollider->Move(Vector3((1 + (attackRange / 2)), 0, 0));

	}
	facingRight = !facingRight;
	graphics->MapToBuffer(facingDirBuffer, &facingRight, sizeof(bool));
	curVelocity.x *= -1;
}
void Enemy::ApplyGravity()
{
	curVelocity += Vector3::Down * gravity * deltaTime;
}
void Enemy::InitializeShaders()
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	shaders = new ShaderClass();
	shaders->CreateVS(graphics->device, L"EnemyVertex.hlsl", inputDesc, numElements);
	shaders->CreatePS(graphics->device, L"EnemyPixel.hlsl");
}

void Enemy::CheckNextFrameCollision()
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
			SwitchWalkingDir();
		}
	}
	if (facingRight)
	{
		if (!collisionHandler->IsPointCollidingWithLevel(position + Vector3(modelWidth, -1.0f, 0)))
		{
			SwitchWalkingDir();
		}
	}
	else
	{
		if (!collisionHandler->IsPointCollidingWithLevel(position + Vector3(0, -1.0f, 0)))
		{
			SwitchWalkingDir();
		}
	}
}

void Enemy::CreateDrawable()
{
	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(graphics->camera.GetViewProjBuffer());
	vsConstantBuffers.push_back(moveBuffer);
	vsConstantBuffers.push_back(currentAnimationBuffer);
	vsConstantBuffers.push_back(facingDirBuffer);
	vector<ID3D11ShaderResourceView*> psResourceViews;
	psResourceViews.push_back(texture.GetResourceView());

	std::vector<Graphics::LevelBlockVertex> vertices;
	vertices.push_back({ position + Vector3(0,height,0)		,Vector2(0,0) });
	vertices.push_back({ position + Vector3(width,0,0)		,Vector2(1,1) });
	vertices.push_back({ position							,Vector2(0,1) });
	vertices.push_back({ position + Vector3(width,height,0)	,Vector2(1,0) });

	drawableIndex = graphics->CreateDrawable(vertices, shaders, sizeof(Graphics::LevelBlockVertex), graphics->squareIndexBuffer, vsConstantBuffers, psResourceViews);
}

void Enemy::Move()
{
	if (isWalking)
	{
		Vector3 finalVelocity = (curVelocity)*deltaTime;
		if (collisionHandler->isCollidingAfterMove(collider, finalVelocity) == nullptr)
		{
			previousTranslation += finalVelocity;
			moveMatrix = Matrix::CreateTranslation(previousTranslation);
			position += finalVelocity;
			collider->Move(finalVelocity);
			attackCollider->Move(finalVelocity);
			graphics->MapToBuffer(moveBuffer, &moveMatrix, sizeof(Matrix));
		}
	}
}

bool Enemy::IsGrounded()
{
	return collisionHandler->isCollidingAfterMove(collider, Vector3::Down * 0.1f) && curVelocity.y <= 0;
}

void Enemy::ObservePlayer(Vector3 playerPos)
{
	float xDistance = abs(playerPos.x - position.x);
	float yDistance = abs(playerPos.y - position.y);
	if (yDistance < 1 && xDistance <= detectionRange)
	{
		if (facingRight)
		{
			if (position.x > playerPos.x)
			{
				SwitchWalkingDir();
			}
		}
		else
		{
			if (position.x < playerPos.x)
			{
				SwitchWalkingDir();
			}
		}
		if (xDistance < attackRange)
		{
			Attack();
		}
	}
}

void Enemy::Attack()
{
	if (currentAnimation->animationType != Animation::AnimationType::Attack)
	{
		isWalking = false;
		currentAnimation = attackAnimation->Play(currentAnimationBuffer, currentAnimation);
		std::vector<BoxCollider*> hits = collisionHandler->GetCollisions(attackCollider);
		for (int i = 0; i < hits.size() && !damagedPlayer; i++)
		{
			damagedPlayer = hits[i]->unitIndex == 0;
		}
	}
}
