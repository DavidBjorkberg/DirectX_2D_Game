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
	Game();
	Game(float* deltaTime);
	~Game();
private:
	float* deltaTime;
	Texture backgroundTexture;
	Texture fullHeartsTexture;
	Texture emptyHeartsTexture;
	ShaderClass backgroundShaders;
	ShaderClass healthUIShaders;
	LevelManager levelManager;
	Graphics graphics;
	CollisionHandler collisionHandler;
	void CreateBackground();
	void CreateHealthUI();
};