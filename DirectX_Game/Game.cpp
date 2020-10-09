#include "Game.h"

void Game::Initialize(HWND handle)
{
	graphics = Graphics(handle);
	levelManager = LevelManager(&graphics, &collisionHandler);
	keyboard = std::make_unique<DirectX::Keyboard>();
	player = Player(Vector3(-2.0f,2.0f, 0),&graphics,&collisionHandler);
}

void Game::Update()
{
	float clearColor[4] = { 0,0,1,1 };
	graphics.deviceContext->ClearRenderTargetView(graphics.renderTargetView, clearColor);
	graphics.Draw();
	player.Update(*deltaTime,keyboard->GetState());
	graphics.swapChain->Present(0, 0);
}

void Game::HandleInput()
{
	/*float xMove = 0;
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
	graphics.MoveCamera(xMove, yMove);*/
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


