#include "Player.h"

void Player::Update(float deltaTime, DirectX::Keyboard::State kb)
{
	CalculateVelocity(kb, deltaTime);
	Move(deltaTime);
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
		pos + Vector3(width,0,0),
		pos,
		pos + Vector3(width,height,0)
	};
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		//{"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
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
	collider = new BoxCollider(pos, 1, 1);
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
void Player::Move(float deltaTime)
{
	if (collisionHandler->isCollidingNextFrame(collider, velocity * deltaTime) == nullptr)
	{
		previousTranslation += velocity * deltaTime;
		moveMatrix = Matrix::CreateTranslation(previousTranslation);
		collider->Move(velocity * deltaTime);

		D3D11_MAPPED_SUBRESOURCE mappedMemory;
		HRESULT hr = graphics->deviceContext->Map(moveBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
		memcpy(mappedMemory.pData, &moveMatrix, sizeof(Matrix));
		graphics->deviceContext->Unmap(moveBuffer, 0);
	}
}

void Player::CalculateVelocity(DirectX::Keyboard::State kb, float deltaTime)
{
	velocity = Vector3::Down * gravity;
	if (kb.A)
	{
		velocity += Vector3::Left * movementSpeed;
	}
	if (kb.D)
	{
		velocity += Vector3::Right * movementSpeed;
	}

	BoxCollider* collidedWith = collisionHandler->isCollidingNextFrame(collider, velocity * deltaTime);
	if (collidedWith != nullptr)
	{
		if (!collider->IsCollidingNextFrame(collidedWith, Vector3(velocity.x, 0, 0) * deltaTime))
		{
			velocity.y = 0;
		}
		else if (!collider->IsCollidingNextFrame(collidedWith, Vector3(0, velocity.y, 0) * deltaTime))
		{
			velocity.x = 0;
		}
		else
		{
			velocity = Vector3::Zero;
		}

	}
}

