#pragma once
#include "LevelManager.h"
#include"Graphics.h"
#include"Keyboard.h"
class Game
{
public:
	void Initialize(HWND handle);
	void Update();
	void HandleInput();
	std::unique_ptr<DirectX::Keyboard> keyboard;
	Game();
private:
	LevelManager levelManager;
	Graphics graphics;
	void DrawScene();
};