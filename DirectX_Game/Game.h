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
	ShaderClass backgroundShaders;
	ID3D11Buffer* bgVertexBuffer;
	LevelManager levelManager;
	Graphics graphics;
	CollisionHandler collisionHandler;
	void DrawScene();
	void CreateBackground();
};