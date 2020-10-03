#include "Game.h"

void Game::Initialize(HWND handle)
{
	graphics = Graphics(handle);
	levelManager = LevelManager(&graphics);
	levelManager.AddBlock();
	keyboard = std::make_unique<DirectX::Keyboard>();
}

void Game::Update()
{
	HandleInput();
	float clearColor[4] = { 0,0,1,1 };
	graphics.deviceContext->ClearRenderTargetView(graphics.renderTargetView, clearColor);
	DrawScene();
	graphics.swapChain->Present(0, 0);
}

void Game::HandleInput()
{
	auto input = keyboard->GetState();
	float xMove = 0;
	float yMove = 0;
	float movementSpeed = 0.0001f;
	if (input.A)
	{
		xMove -= movementSpeed;
	}
	if (input.D)
	{
		xMove += movementSpeed;
	}
	if (input.S)
	{
		yMove -= movementSpeed;
	}
	if (input.W)
	{
		yMove += movementSpeed;
	}
	graphics.MoveCamera(xMove, yMove);
}

Game::Game()
{
}

void Game::DrawScene()
{
	levelManager.DrawLevel(graphics.deviceContext);
}
