#pragma once
#include "LevelManager.h"
#include"Graphics.h"
class Game
{
public:
	void Initialize(HWND handle);
	void Update();
	Game();
private:
	LevelManager levelManager;
	Graphics graphics;
	void DrawScene();
};