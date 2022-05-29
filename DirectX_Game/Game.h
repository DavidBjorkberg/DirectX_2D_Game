#pragma once
#include "LevelManager.h"
#include"Graphics.h"
#include"CollisionHandler.h"
#include "Camera.h"
#include "Input.h"
class Game
{
public:
	Game();
	Game(float* deltaTime);
	~Game();
	void Initialize(HWND handle);
	void Update();
	static Camera* GetMainCamera();
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