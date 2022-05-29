#pragma once
#include<vector>
#include"LevelBlock.h"
#include"Graphics.h"
#include"Player.h"
#include"LevelReader.h"
#include"Enemy.h"
#include "Entity.h"
#define STB_IMAGE_IMPLEMENTATION
class LevelManager
{
public:
	std::vector<LevelBlock*> level;
	std::vector<Enemy*> enemies;
	Entity* playerGO = nullptr;
	void UpdateComponents(float deltaTime);
	static void AddGameObject(Entity* gameObject);
	LevelManager();
	LevelManager(Graphics* graphics);
private:
	Graphics* graphics;
	LevelReader* levelReader;
	static std::vector<Entity*> gameObjects;
	void UpdateEnemies(float deltaTime);
	void CreateEnemy(Vector2 position, string type);
	void CreatePlayer();
};