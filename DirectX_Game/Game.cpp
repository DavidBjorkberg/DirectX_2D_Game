#include "Game.h"

void Game::Initialize(HWND handle)
{
	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	graphics = Graphics(handle);
	CreateBackground();
	levelManager = LevelManager(&graphics, &collisionHandler);
	graphics.camera.Init(levelManager.player.playerMovement->position);
	CreateHealthUI();

}

void Game::Update()
{
	levelManager.Update(*deltaTime);
	graphics.Update();
}
Game::Game()
{
}

Game::Game(float* deltaTime)
{
	this->deltaTime = deltaTime;
}

Game::~Game()
{
}

void Game::CreateBackground()
{
	backgroundTexture.Initialize(graphics.device, graphics.deviceContext, "Textures/Background.png");
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	backgroundShaders.CreateVS(graphics.device, L"BGVertex.hlsl", inputDesc, numElements);
	backgroundShaders.CreatePS(graphics.device, L"BGPixel.hlsl");
	std::vector<Graphics::LevelBlockVertex> vertices;
	vertices.push_back({ Vector3(-1,1,0),Vector2(0,0), });
	vertices.push_back({ Vector3(1,-1,0),Vector2(1,1), });
	vertices.push_back({ Vector3(-1,-1,0),Vector2(0,1), });
	vertices.push_back({ Vector3(1,1,0),Vector2(1,0), });

	vector<ID3D11ShaderResourceView*> psResourceViews;
	psResourceViews.push_back(backgroundTexture.GetResourceView());

	graphics.CreateDrawable(vertices, &backgroundShaders, sizeof(Graphics::LevelBlockVertex)
		, graphics.squareIndexBuffer, vector<ID3D11Buffer*>(), psResourceViews);
}

void Game::CreateHealthUI()
{
	fullHeartsTexture.Initialize(graphics.device, graphics.deviceContext, "Textures/Hearts.png");
	emptyHeartsTexture.Initialize(graphics.device, graphics.deviceContext, "Textures/EmptyHearts.png");
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	healthUIShaders.CreateVS(graphics.device, L"HealthUIVertex.hlsl", inputDesc, numElements);
	healthUIShaders.CreatePS(graphics.device, L"HealthUIPixel.hlsl");
	std::vector<Graphics::LevelBlockVertex> vertices;
	vertices.push_back({ Vector3(0.5f,1.0f,0),Vector2(0,0), });
	vertices.push_back({ Vector3(1.0f,0.9f,0),Vector2(1,1), });
	vertices.push_back({ Vector3(0.5f,0.9f,0),Vector2(0,1), });
	vertices.push_back({ Vector3(1.0f,1.0f,0),Vector2(1,0), });

	vector<ID3D11Buffer*> psConstantBuffers;
	psConstantBuffers.push_back(levelManager.player.healthBuffer);
	vector<ID3D11ShaderResourceView*> psResourceViews;
	psResourceViews.push_back(fullHeartsTexture.GetResourceView());
	psResourceViews.push_back(emptyHeartsTexture.GetResourceView());

	graphics.CreateDrawable(vertices, &healthUIShaders, sizeof(Graphics::LevelBlockVertex)
		, graphics.squareIndexBuffer, vector<ID3D11Buffer*>(), psResourceViews,psConstantBuffers);
}


