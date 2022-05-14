#include "LevelManager.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Component.h"
#include "PlayerMovement2.h"
#include "Physics.h"
std::vector<Entity*> LevelManager::gameObjects;
void LevelManager::UpdateComponents(float deltaTime)
{
	playerGO->UpdateComponents(deltaTime);
	UpdateEnemies(deltaTime);
}

void LevelManager::AddGameObject(Entity* gameObject)
{
	gameObjects.push_back(gameObject);
}

LevelManager::LevelManager()
{
}

LevelManager::LevelManager(Graphics* graphics)
{
	this->levelReader = new LevelReader(graphics, &level);
	this->graphics = graphics;
	levelReader->ReadLevel("Textures/TestLevel.png");
	std::vector<Component*>* playerComponents = new vector<Component*>();
	playerComponents->push_back(new Transform(levelReader->playerSpawnPos));
	playerComponents->push_back(new BoxCollider(levelReader->playerSpawnPos, 2, 2, Physics::PropLayer)); //TODO: Define width & height better than just '2'. Sprite size?
	playerComponents->push_back(new SpriteRenderer("Textures/Player_SpriteSheet.png", 2, 2, graphics, Vector4::Zero, "PlayerVertex.hlsl", "PlayerPixel.hlsl"));
	playerComponents->push_back(new Rigidbody());
	playerComponents->push_back(new PlayerMovement2());
	playerGO = new Entity(playerComponents);
	gameObjects.push_back(playerGO);

	playerGO->GetComponent<Transform>()->SetPosition(levelReader->playerSpawnPos);
	for (int i = 0; i < levelReader->tallEnemySpawnPos.size(); i++)
	{
		//enemies.push_back(new TallBoyEnemy(levelReader->tallEnemySpawnPos[i], graphics, collisionHandler, enemies.size() + 1));
	}
	for (int i = 0; i < levelReader->shortEnemySpawnPos.size(); i++)
	{
		//enemies.push_back(new ShortBoyEnemy(levelReader->shortEnemySpawnPos[i], graphics, collisionHandler, enemies.size() + 1));
	}
}

void LevelManager::UpdateEnemies(float deltaTime)
{
	/*std::vector<int> hitEnemyIndices = player->GetEnemyHitIndices();
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
			enemies[i]->Update(player->playerMovement->position, deltaTime, player->IsAlive());
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->damagedPlayer)
		{
			player->TakeDamage();
		}
	}*/
}


