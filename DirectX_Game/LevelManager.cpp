#include "LevelManager.h"

void LevelManager::Update(float deltaTime)
{
	player.Update(deltaTime);
	UpdateEnemies(deltaTime);
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
	for (int i = 0; i < levelReader->tallEnemySpawnPos.size(); i++)
	{
		enemies.push_back(new TallBoyEnemy(levelReader->tallEnemySpawnPos[i], graphics, collisionHandler, enemies.size() + 1));
	}
	for (int i = 0; i < levelReader->shortEnemySpawnPos.size(); i++)
	{
		enemies.push_back(new ShortBoyEnemy(levelReader->shortEnemySpawnPos[i], graphics, collisionHandler, enemies.size() + 1));
	}
	InitializeColliders();
}
void LevelManager::InitializeColliders()
{
	for (int i = 0; i < level.size(); i++)
	{
		this->collisionHandler->AddCollider(level[i]->collider);
	}
}

void LevelManager::UpdateEnemies(float deltaTime)
{
	std::vector<int> hitEnemyIndices = player.GetEnemyHitIndices();
	for (int i = 0; i < hitEnemyIndices.size(); i++)
	{
		for (int j = 0; j < enemies.size(); j++)
		{
			if (enemies[j]->collider->unitIndex == hitEnemyIndices[i])
			{
				enemies[j]->TakeDamage();
			}
		}
	}
	for (int i = enemies.size() - 1; i >= 0; i--)
	{
		if (enemies[i]->isToBeRemoved)
		{
			graphics->RemoveDrawable(enemies[i]->drawableIndex);
			collisionHandler->RemoveCollider(enemies[i]->collider);
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		else
		{
			enemies[i]->Update(player.playerMovement->position, deltaTime, player.IsAlive());
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->damagedPlayer)
		{
			player.TakeDamage();
		}
	}
}


