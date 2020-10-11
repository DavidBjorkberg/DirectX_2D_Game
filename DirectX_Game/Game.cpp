#include "Game.h"

void Game::Initialize(HWND handle)
{
	graphics = Graphics(handle);
	CreateBackground();
	levelManager = LevelManager(&graphics, &collisionHandler);
	keyboard = std::make_unique<DirectX::Keyboard>();
	player = Player(Vector3(-2.0f, 2.0f, 0), &graphics, &collisionHandler);
}

void Game::Update()
{
	player.Update(*deltaTime, keyboard->GetState());
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
	keyboard.release();
}

void Game::DrawScene()
{
}

void Game::CreateBackground()
{
	backgroundTexture.Initialize(graphics.device, graphics.deviceContext, "Background.png");
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

	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(graphics.camera.GetViewProjBuffer());

	vector<ID3D11ShaderResourceView*> psResourceViews;
	psResourceViews.push_back(backgroundTexture.GetResourceView());

	graphics.CreateDrawable(vertices, &backgroundShaders, bgVertexBuffer, sizeof(Graphics::LevelBlockVertex)
		, graphics.squareIndexBuffer, vsConstantBuffers, psResourceViews);
}


