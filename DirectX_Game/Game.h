#pragma once
#include "LevelManager.h"
#include"Graphics.h"
#include"CollisionHandler.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
class Game
{
public:
	void Initialize(HWND handle);
	void Update();
	static Camera* GetMainCamera();
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
	static Camera* mainCamera;
	static Input* input;
	void CreateBackground();
	void CreateHealthUI();
};