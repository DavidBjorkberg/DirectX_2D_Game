#include "LevelManager.h"

void LevelManager::Update(float deltaTime)
{
	player.Update(deltaTime);

	std::vector<int> hitEnemyIndices = player.GetEnemyHitIndices();
	for (int i = 0; i < hitEnemyIndices.size(); i++)
	{
		//Deal damage
	}
}

LevelManager::LevelManager()
{
}

LevelManager::LevelManager(Graphics* graphics, CollisionHandler* collisionHandler)
{
	this->levelReader = new LevelReader(graphics, &level);
	this->graphics = graphics;
	this->collisionHandler = collisionHandler;
	levelReader->ReadLevel("Textures/Level.png");
	player = Player(levelReader->playerSpawnPos, graphics, collisionHandler);
	InitializeColliders();
}

void LevelManager::InitializeColliders()
{
	for (int i = 0; i < level.size(); i++)
	{
		this->collisionHandler->AddCollider(level[i]->collider);
	}
	
}


