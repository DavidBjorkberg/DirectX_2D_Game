#include "Player.h"

void Player::Update(float deltaTime, DirectX::Keyboard::State kb)
{
	this->deltaTime = deltaTime;
	ApplyGravity(kb);

	GetInput(kb);
	ClampVelocity();

	CheckNextFrameCollision();
	Move();
	ApplyGravity(kb);
}

Vector3 Player::GetPosition()
{
	return position;
}
Player::Player(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler)
{
	this->position = pos;
	this->graphics = graphics;
	this->collisionHandler = collisionHandler;
	Graphics::LevelBlockVertex vertices[4] =
	{
		pos + Vector3(0,height,0),
		Vector2(0,0),
		pos + Vector3(width,0,0),
		Vector2(1,1),
		pos,
		Vector2(0,1),
		pos + Vector3(width,height,0),
		Vector2(1,0)
	};
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	shaders = new ShaderClass();
	shaders->CreateVS(graphics->device, L"PlayerVertex.hlsl", inputDesc, numElements);
	shaders->CreatePS(graphics->device, L"PlayerPixel.hlsl");

	graphics->CreateConstantBuffer(&moveBuffer, sizeof(Matrix));

	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = graphics->deviceContext->Map(moveBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &moveMatrix, sizeof(Matrix));
	graphics->deviceContext->Unmap(moveBuffer, 0);

	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(graphics->camera.GetViewProjBuffer());
	vsConstantBuffers.push_back(moveBuffer);
	collider = new BoxCollider(pos, width, height);
	collisionHandler->AddCollider(collider);
	CreateIndexBuffer(graphics);
	graphics->CreateDrawable(vertices, sizeof(vertices), shaders, vertexBuffer, sizeof(Graphics::LevelBlockVertex), indexBuffer, vsConstantBuffers);
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
	AddVelocity(Vector3(curVelocity.x, jumpForce, 0), VelocityMode::Force);
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
	if (velocityMode == VelocityMode::Instant)
	{
		curVelocity += addVelocity;
	}
	else if (velocityMode == VelocityMode::Force)
	{
		curVelocity = addVelocity;
	} 
}
void Player::ApplyGravity(DirectX::Keyboard::State kb)
{
	//For high jump
	if (curVelocity.y < 0)
	{
		AddVelocity(Vector3::Down * gravity * 2 * deltaTime, VelocityMode::Instant);
	}
	else if (curVelocity.y > 0 && !kb.Space)
	{
		AddVelocity(Vector3::Down * gravity * 2 * deltaTime, VelocityMode::Instant);
	}
	//Regular gravity 
	AddVelocity(Vector3::Down * gravity * deltaTime, VelocityMode::Instant);
}

void Player::GetInput(DirectX::Keyboard::State kb)
{
	if (kb.A)
	{
		AddVelocity(Vector3::Left * acceleration * deltaTime, VelocityMode::Instant);
	}
	else if (kb.D)
	{
		AddVelocity(Vector3::Right * acceleration * deltaTime, VelocityMode::Instant);
	}
	else if(IsGrounded())
	{
		if (curVelocity.x > 0)
		{
			AddVelocity(Vector3::Left * acceleration * deltaTime, VelocityMode::Instant);
			if (curVelocity.x < 0)
			{
				curVelocity.x = 0;
			}
		}
		else
		{
			AddVelocity(Vector3::Right * acceleration * deltaTime, VelocityMode::Instant);
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
	return collisionHandler->isCollidingAfterMove(collider, Vector3::Down * 0.1f);
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

