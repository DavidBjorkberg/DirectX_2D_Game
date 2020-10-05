#include "Player.h"

void Player::Update(float deltaTime)
{
}

Vector3 Player::GetPosition()
{
	return position;
}

Player::Player(Vector3 pos,Graphics* graphics)
{
	this->position = pos;
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

	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(graphics->camera.GetViewProjBuffer());
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
