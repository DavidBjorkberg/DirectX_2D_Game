#include "Game.h"

void Game::Initialize(HWND handle)
{
	graphics = Graphics(handle);
	graphics.Init();
	levelManager = LevelManager(&graphics);
	levelManager.AddBlock();
}

void Game::Update()
{
	float clearColor[4] = { 0,0,1,1 };
	graphics.deviceContext->ClearRenderTargetView(graphics.renderTargetView, clearColor);
	DrawScene();
	graphics.swapChain->Present(0, 0);
}

Game::Game()
{
}

void Game::DrawScene()
{
	levelManager.DrawLevel(graphics.deviceContext);
}
