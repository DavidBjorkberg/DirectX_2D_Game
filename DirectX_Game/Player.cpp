#include "Player.h"

void Player::Update(float deltaTime)
{
	hitEnemyIndices.clear();
	this->deltaTime = deltaTime;
	if (keyboard->GetState().X && currentAnimation->animationType != Animation::AnimationType::Attack)
	{
		Attack();
	}
	UpdateAnimation();
	if (IsAlive())
	{
		playerMovement->Update(deltaTime, &currentAnimation, currentAnimationBuffer);
	}
}

bool Player::IsAlive()
{
	return currentHealth > 0;
}

std::vector<int> Player::GetEnemyHitIndices()
{
	return hitEnemyIndices;
}

Player::Player(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler)
{
	keyboard = std::make_unique<DirectX::Keyboard>();
	currentHealth = maxHealth;
	healthPercent = 1;
	this->graphics = graphics;

	texture.Initialize(graphics->device, graphics->deviceContext, "Textures/Player_SpriteSheet.png");
	graphics->CreateConstantBuffer(&healthBuffer, 16);
	graphics->CreateConstantBuffer(&currentAnimationBuffer, 16);
	graphics->MapToBuffer(healthBuffer, &healthPercent, sizeof(float));

	InitializeShaders();
	playerMovement = new PlayerMovement(pos, width, height, collisionHandler, &currentAnimation, &currentAnimationBuffer, graphics, keyboard.get());
	jumpAnimation = new Animation(graphics, Animation::AnimationType::Jump, false);
	idleAnimation = new Animation(graphics, Animation::AnimationType::Idle);
	runAnimation = new Animation(graphics, Animation::AnimationType::Run);
	attackAnimation = new Animation(graphics, Animation::AnimationType::Attack, false, 10);
	hitAnimation = new Animation(graphics, Animation::AnimationType::Hit, false, 20);
	deathAnimation = new Animation(graphics, Animation::AnimationType::Death, false);
	currentAnimation = idleAnimation->Play(currentAnimationBuffer, currentAnimation);
	CreateDrawable(pos);

}

Player::Player()
{
}
void Player::Attack()
{
	std::vector<BoxCollider*> hits = playerMovement->collisionHandler->GetCollisions(playerMovement->attackCollider);

	for (int i = 0; i < hits.size(); i++)
	{
		if (hits[i]->unitIndex > 0)
		{
			hitEnemyIndices.push_back(hits[i]->unitIndex);
		}
	}
}

void Player::TakeDamage()
{
	currentHealth -= 2;
	playerMovement->canMove = false;
	healthPercent = currentHealth / maxHealth;
	graphics->MapToBuffer(healthBuffer, &healthPercent, sizeof(float));
	if (currentHealth > 0)
	{
		currentAnimation = hitAnimation->Play(currentAnimationBuffer, currentAnimation);
	}
	else
	{
		currentAnimation = deathAnimation->Play(currentAnimationBuffer, currentAnimation);
	}
}

void Player::InitializeShaders()
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	shaders = new ShaderClass();
	shaders->CreateVS(graphics->device, L"PlayerVertex.hlsl", inputDesc, numElements);
	shaders->CreatePS(graphics->device, L"PlayerPixel.hlsl");
}

void Player::CreateDrawable(Vector3 position)
{
	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(graphics->camera.GetViewProjBuffer());
	vsConstantBuffers.push_back(playerMovement->moveBuffer);
	vsConstantBuffers.push_back(currentAnimationBuffer);
	vsConstantBuffers.push_back(playerMovement->facingDirBuffer);
	vector<ID3D11ShaderResourceView*> psResourceViews;
	psResourceViews.push_back(texture.GetResourceView());

	std::vector<Graphics::LevelBlockVertex> vertices;
	vertices.push_back({ position + Vector3(0,height,0)		,Vector2(0,0) });
	vertices.push_back({ position + Vector3(width,0,0)		,Vector2(1,1) });
	vertices.push_back({ position							,Vector2(0,1) });
	vertices.push_back({ position + Vector3(width,height,0)	,Vector2(1,0) });

	graphics->CreateDrawable(vertices, shaders, sizeof(Graphics::LevelBlockVertex), graphics->squareIndexBuffer, vsConstantBuffers, psResourceViews);
}


void Player::UpdateAnimation()
{
	DirectX::Keyboard::State kb = keyboard->GetState();
	switch (currentAnimation->animationType)
	{
	case Animation::AnimationType::Attack:
		if (!currentAnimation->isPlaying)
		{
			currentAnimation = idleAnimation->Play(currentAnimationBuffer, currentAnimation);
		}
		break;
	case Animation::AnimationType::Hit:
		if (!currentAnimation->isPlaying)
		{
			currentAnimation = idleAnimation->Play(currentAnimationBuffer, currentAnimation);
			playerMovement->canMove = true;
		}
		break;
	case Animation::AnimationType::Death:
		break;
	default:
		if (kb.X)
		{
			currentAnimation = attackAnimation->Play(currentAnimationBuffer, currentAnimation);
		}
		else if (playerMovement->IsGrounded())
		{
			if (kb.Space)
			{
				currentAnimation = jumpAnimation->Play(currentAnimationBuffer, currentAnimation);
			}
			else if (kb.A || kb.D)
			{
				currentAnimation = runAnimation->Play(currentAnimationBuffer, currentAnimation);
			}
			else
			{
				currentAnimation = idleAnimation->Play(currentAnimationBuffer, currentAnimation);
			}
		}
		break;
	}
	currentAnimation->Update(deltaTime, currentAnimationBuffer);
}

