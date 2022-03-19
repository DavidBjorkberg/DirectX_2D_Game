#pragma once
#include<vector>
#include"LevelBlock.h"
#include"Graphics.h"
#include "stb_image.h"
#include"CollisionHandler.h"
#include"Player.h"
#include"LevelReader.h"
#include"TallBoyEnemy.h"
#include"ShortBoyEnemy.h"
#include "PlayerGameObject.h"
#define STB_IMAGE_IMPLEMENTATION
class LevelManager
{
public:
	std::vector<LevelBlock*> level;
	std::vector<Enemy*> enemies;
	PlayerGameObject* player;
	void UpdateComponents(float deltaTime);
	LevelManager();
	LevelManager(Graphics* graphics,CollisionHandler* collisionHandler);
private:
	Graphics* graphics;
	CollisionHandler* collisionHandler;
	LevelReader* levelReader;
	void InitializeColliders();
	void UpdateEnemies(float deltaTime);
};