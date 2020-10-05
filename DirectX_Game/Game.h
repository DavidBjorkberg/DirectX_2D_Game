#pragma once
#include "LevelManager.h"
#include"Graphics.h"
#include"CollisionHandler.h"
#include"Keyboard.h"
#include "Player.h"
class Game
{
public:
	void Initialize(HWND handle);
	void Update();
	void HandleInput();
	std::unique_ptr<DirectX::Keyboard> keyboard;
	Game();
	Game(float* deltaTime);
private:
	Player player;
	float* deltaTime;
	LevelManager levelManager;
	Graphics graphics;
	CollisionHandler collisionHandler;
	void DrawScene();
};