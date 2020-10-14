#include "Player.h"

void Player::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	playerMovement->Update(deltaTime,&currentAnimation,currentAnimationBuffer);
	UpdateAnimation();
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

	texture.Initialize(graphics->device, graphics->deviceContext, "Textures/Player_SpriteSheet.png");
	graphics->CreateConstantBuffer(&currentAnimationBuffer, 16);

	InitializeShaders();
	CreateIndexBuffer(graphics);
	playerMovement = new PlayerMovement(pos, width, height, collisionHandler,&currentAnimation,&currentAnimationBuffer,graphics,keyboard.get());
	attackCollider = new BoxCollider(position + Vector3(0.4f, 0.1f, 0) + Vector3(attackRange / 2, 0, 0), attackRange, attackHeight);
	currentAnimation = playerMovement->jumpAnimation->Play(currentAnimationBuffer);
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
void Player::Attack()
{

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

	graphics->CreateDrawable(vertices, shaders, vertexBuffer, sizeof(Graphics::LevelBlockVertex), indexBuffer, vsConstantBuffers, psResourceViews);
}


void Player::UpdateAnimation()
{
	DirectX::Keyboard::State kb = keyboard->GetState();
	if (currentAnimation->animationType == Animation::AnimationType::Jump
		&& playerMovement->IsGrounded())
	{
		if (kb.A || kb.D)
		{
			currentAnimation = playerMovement->runAnimation->Play(currentAnimationBuffer);
		}
		else
		{
			currentAnimation = playerMovement->idleAnimation->Play(currentAnimationBuffer);
		}
	}

	currentAnimation->Update(deltaTime, currentAnimationBuffer);

	if (!currentAnimation->isPlaying)
	{
		if (currentAnimation->animationType != Animation::AnimationType::Jump)
		{
			if (kb.A || kb.D)
			{
				currentAnimation = playerMovement->runAnimation->Play(currentAnimationBuffer);
			}
			else
			{
				currentAnimation = playerMovement->idleAnimation->Play(currentAnimationBuffer);
			}
		}
	}

}

