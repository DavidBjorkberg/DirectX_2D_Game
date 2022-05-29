#include "Game.h"
#include "Transform.h"
#include "SpriteRenderer.h"
Camera* Game::mainCamera;
Input* Game::input;
//TODO:
//Merge all shaders into one?
//Make all member variables start with capital
void Game::Initialize(HWND handle)
{
	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	graphics = Graphics(handle);
	mainCamera = new Camera(&graphics);
	Physics::InitializeLayers();
	CreateBackground();
	levelManager = LevelManager(&graphics);
	mainCamera->SetFollowTarget(levelManager.playerGO);
	CreateHealthUI();
	this->input = new Input();
}

void Game::Update()
{
	Input::Update();
	levelManager.UpdateComponents(*deltaTime);
	mainCamera->Update();
	graphics.Update();
}
Camera* Game::GetMainCamera()
{
	return mainCamera;
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
	delete mainCamera;
	delete input;
}

void Game::CreateBackground()
{
	std::vector<Component*>* playerComponents = new vector<Component*>();
	playerComponents->push_back(new SpriteRenderer("Textures/Background.png", 2, 2, &graphics, Vector4::Zero, "BGVertex.hlsl", "BGPixel.hlsl"));

	levelManager.AddGameObject(new Entity(playerComponents));
}

void Game::CreateHealthUI() //TODO: Reimplement with entity component
{
	//fullHeartsTexture.Initialize(graphics.device, graphics.deviceContext, "Textures/Hearts.png");
	//emptyHeartsTexture.Initialize(graphics.device, graphics.deviceContext, "Textures/EmptyHearts.png");
	//D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	//{
	//	{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	//	{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	//};
	//UINT numElements = ARRAYSIZE(inputDesc);
	//healthUIShaders.CreateVS(graphics.device, L"HealthUIVertex.hlsl", inputDesc, numElements);
	//healthUIShaders.CreatePS(graphics.device, L"HealthUIPixel.hlsl");
	//std::vector<Graphics::Vertex> vertices;
	//vertices.push_back({ Vector3(0.5f,1.0f,0),Vector2(0,0), });
	//vertices.push_back({ Vector3(1.0f,0.9f,0),Vector2(1,1), });
	//vertices.push_back({ Vector3(0.5f,0.9f,0),Vector2(0,1), });
	//vertices.push_back({ Vector3(1.0f,1.0f,0),Vector2(1,0), });

	//vector<ID3D11Buffer*> psConstantBuffers;
	//psConstantBuffers.push_back(levelManager.playerGO->healthBuffer);
	//vector<ID3D11ShaderResourceView*> psResourceViews;
	//psResourceViews.push_back(fullHeartsTexture.GetResourceView());
	//psResourceViews.push_back(emptyHeartsTexture.GetResourceView());

	//graphics.CreateDrawable(vertices, &healthUIShaders, sizeof(Graphics::Vertex)
	//	, graphics.squareIndexBuffer, vector<ID3D11Buffer*>(), psResourceViews, psConstantBuffers);
}


