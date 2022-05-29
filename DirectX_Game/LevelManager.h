#pragma once
#include<vector>
#include"LevelBlock.h"
#include"Graphics.h"
#include"LevelReader.h"
#include "Entity.h"
#define STB_IMAGE_IMPLEMENTATION
class LevelManager
{
public:
	LevelManager();
	LevelManager(Graphics* graphics);
	virtual ~LevelManager();
	std::vector<LevelBlock*> level;
	Entity* playerGO = nullptr;
	void UpdateComponents(float deltaTime);
	static void AddGameObject(Entity* gameObject);
private:
	Graphics* graphics;
	LevelReader* levelReader;
	static std::vector<Entity*> gameObjects;
	void CreateEnemy(Vector2 position, string type);
	void CreatePlayer();
};