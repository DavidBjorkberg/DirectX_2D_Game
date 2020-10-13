#include "Player.h"

void Player::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	UpdateAnimation();
	ApplyGravity();

	GetInput();
	ClampVelocity();

	CheckNextFrameCollision();
	Move();
	ApplyGravity();

}

Vector3 Player::GetPosition()
{
	return position;
}
Player::Player(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler)
{
	keyboard = std::make_unique<DirectX::Keyboard>();

	this->position = pos;
	this->graphics = graphics;
	this->collisionHandler = collisionHandler;

	texture.Initialize(graphics->device, graphics->deviceContext, "Textures/Player_SpriteSheet.png");
	graphics->CreateConstantBuffer(&moveBuffer, sizeof(Matrix));
	graphics->CreateConstantBuffer(&currentAnimationBuffer, 16);
	graphics->CreateConstantBuffer(&facingDirBuffer, 16);
	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = graphics->deviceContext->Map(facingDirBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &facingRight, sizeof(bool));
	graphics->deviceContext->Unmap(facingDirBuffer, 0);
	InitializeShaders();
	CreateIndexBuffer(graphics);

	collider = new BoxCollider(position + Vector3(0.4f, 0.1f, 0), width - 1.4f, height - 0.8f);
	collisionHandler->AddCollider(collider);

	jumpAnimation = new Animation(graphics, Animation::AnimationType::Jump);
	idleAnimation = new Animation(graphics, Animation::AnimationType::Idle);
	runAnimation = new Animation(graphics, Animation::AnimationType::Run);
	currentAnimation = jumpAnimation->Play(currentAnimationBuffer);
	CreateDrawable();

}
void Player::CreateIndexBuffer(Graphics* graphics)
{
	DWORD indices[] = {
	0,  1,  2,
	0,  3,  1,
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 6;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	graphics->device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
}
Player::Player()
{
}
void Player::Move()
{
	Vector3 finalVelocity = (curVelocity)*deltaTime;
	if (collisionHandler->isCollidingAfterMove(collider, finalVelocity) == nullptr)
	{
		previousTranslation += finalVelocity;
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		collider->Move(finalVelocity);
		D3D11_MAPPED_SUBRESOURCE mappedMemory;
		HRESULT hr = graphics->deviceContext->Map(moveBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
		memcpy(mappedMemory.pData, &moveMatrix, sizeof(Matrix));
		graphics->deviceContext->Unmap(moveBuffer, 0);
	}
}
void Player::Jump()
{
	AddVelocity(Vector3(curVelocity.x, jumpForce, 0), VelocityMode::Set);
	currentAnimation = jumpAnimation->Play(currentAnimationBuffer);
}
void Player::CheckNextFrameCollision()
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

void Player::AddVelocity(Vector3 addVelocity, VelocityMode velocityMode)
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
void Player::ApplyGravity()
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

void Player::GetInput()
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
	else if (IsGrounded())
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
	if (kb.IsKeyDown(DirectX::Keyboard::Keys::Space) && IsGrounded() && canJump)
	{
		Jump();
		canJump = false;
	}
	if (kb.IsKeyUp(DirectX::Keyboard::Keys::Space))
	{
		canJump = true;
	}
}

bool Player::IsGrounded()
{
	return collisionHandler->isCollidingAfterMove(collider, Vector3::Down * 0.1f) && curVelocity.y <= 0;
}

void Player::ClampVelocity()
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

void Player::CreateDrawable()
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

	graphics->CreateDrawable(vertices, shaders, vertexBuffer, sizeof(Graphics::LevelBlockVertex), indexBuffer, vsConstantBuffers, psResourceViews);
}

void Player::SwitchFacingDir()
{
	if (facingRight)
	{
		previousTranslation += Vector3(-1, 0, 0);
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		collider->Move(Vector3(-0.4f, 0, 0));
		D3D11_MAPPED_SUBRESOURCE mappedMemory;
		HRESULT hr = graphics->deviceContext->Map(moveBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
		memcpy(mappedMemory.pData, &moveMatrix, sizeof(Matrix));
		graphics->deviceContext->Unmap(moveBuffer, 0);
	}
	else
	{
		previousTranslation += Vector3(1, 0, 0);
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		collider->Move(Vector3(0.4f, 0, 0));
		D3D11_MAPPED_SUBRESOURCE mappedMemory;
		HRESULT hr = graphics->deviceContext->Map(moveBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
		memcpy(mappedMemory.pData, &moveMatrix, sizeof(Matrix));
		graphics->deviceContext->Unmap(moveBuffer, 0);
	}
	facingRight = !facingRight;
	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = graphics->deviceContext->Map(facingDirBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &facingRight, sizeof(bool));
	graphics->deviceContext->Unmap(facingDirBuffer, 0);

}

void Player::UpdateAnimation()
{
	DirectX::Keyboard::State kb = keyboard->GetState();
	if (currentAnimation->animationType == Animation::AnimationType::Jump
		&& IsGrounded())
	{
		if (kb.A || kb.D)
		{
			currentAnimation = runAnimation->Play(currentAnimationBuffer);
		}
		else
		{
			currentAnimation = idleAnimation->Play(currentAnimationBuffer);
		}
	}

	currentAnimation->Update(deltaTime, currentAnimationBuffer);

	if (!currentAnimation->isPlaying)
	{
		if (currentAnimation->animationType != Animation::AnimationType::Jump)
		{
			if (kb.A || kb.D)
			{
				currentAnimation = runAnimation->Play(currentAnimationBuffer);
			}
			else
			{
				currentAnimation = idleAnimation->Play(currentAnimationBuffer);
			}
		}
	}

}

