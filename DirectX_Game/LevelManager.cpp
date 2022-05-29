#include "LevelManager.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Component.h"
#include "PlayerMovement2.h"
#include "Physics.h"
#include "AnimationController.h"
#include "EnemyMovement.h"
#include "HealthComponent.h"
#include "PlayerAttack.h"
#include "EnemyAttack.h"
std::vector<Entity*> LevelManager::gameObjects;
void LevelManager::UpdateComponents(float deltaTime)
{
	for (Entity* entity : gameObjects)
	{
		entity->UpdateComponents(deltaTime);
	}
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
	CreatePlayer();

	for (int i = 0; i < levelReader->tallEnemySpawnPos.size(); i++)
	{
		CreateEnemy(levelReader->tallEnemySpawnPos[i], "TallEnemy");
		//enemies.push_back(new TallBoyEnemy(levelReader->tallEnemySpawnPos[i], graphics, collisionHandler, enemies.size() + 1));
	}
	for (int i = 0; i < levelReader->shortEnemySpawnPos.size(); i++)
	{
		CreateEnemy(levelReader->shortEnemySpawnPos[i], "ShortEnemy");
	}
}

LevelManager::~LevelManager()
{
	delete levelReader;
	for (int i = 0; i < level.size(); i++)
	{
		delete level[i];
	}
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
}

void LevelManager::CreateEnemy(Vector2 position, string type)
{
	std::vector<Component*>* components = new vector<Component*>();
	components->push_back(new Transform(position));
	components->push_back(new Rigidbody());
	components->push_back(new BoxCollider(position, 2, 2, Physics::PlayerLayer)); //TODO: Define width & height better than just '2'. Sprite size?
	components->push_back(new SpriteRenderer("Textures/Player_SpriteSheet2.png", 2, 2, graphics, Vector4::Zero, "PlayerVertex.hlsl", "PlayerPixel.hlsl"));
	HealthComponent* healthComponent = new HealthComponent(3);
	EnemyAttack* enemyAttack = new EnemyAttack();
	components->push_back(healthComponent);
	EnemyMovement* enemyMovement = new EnemyMovement();
	AnimationController* animationController = new AnimationController;
	components->push_back(animationController);
	components->push_back(enemyMovement);

	Animation* runAnimation = new Animation(graphics, "Textures/SpriteSheets/" + type + "_Run_Anim.png");
	Animation* TakeDamageAnimation = new Animation(graphics, "Textures/SpriteSheets/" + type + "_TakeDamage_Anim.png", false);
	Animation* AttackAnimation = new Animation(graphics, "Textures/SpriteSheets/" + type + "_Attack_Anim.png", false);

	runAnimation->transitionPairs = { std::make_pair([healthComponent]() {
	if (healthComponent->tookDamageTrigger)
	{
		healthComponent->tookDamageTrigger = false;
		return true;
	}
	else
	{
		return false;
	}}, TakeDamageAnimation),
	std::make_pair([enemyAttack]() {
	if (enemyAttack->attackTrigger)
	{
		enemyAttack->attackTrigger = false;
		return true;
	}
	else
	{
		return false;
	}}, AttackAnimation) };

	TakeDamageAnimation->transitionPairs = { std::make_pair([TakeDamageAnimation]() {return !TakeDamageAnimation->isPlaying; },runAnimation) };
	AttackAnimation->transitionPairs = { std::make_pair([AttackAnimation]() {return !AttackAnimation->isPlaying; },runAnimation) };
	animationController->Animations = { runAnimation,TakeDamageAnimation, AttackAnimation };

	gameObjects.push_back(new Entity(components));
}

void LevelManager::CreatePlayer()
{
	std::vector<Component*>* playerComponents = new vector<Component*>();
	playerComponents->push_back(new Transform(levelReader->playerSpawnPos));
	playerComponents->push_back(new BoxCollider(levelReader->playerSpawnPos, 2, 2, Physics::PlayerLayer)); //TODO: Define width & height better than just '2'. Sprite size?
	playerComponents->push_back(new SpriteRenderer("Textures/Player_SpriteSheet2.png", 2, 2, graphics, Vector4::Zero, "PlayerVertex.hlsl", "PlayerPixel.hlsl"));
	playerComponents->push_back(new PlayerAttack());
	playerComponents->push_back(new HealthComponent(5));
	Rigidbody* rigidBody = new Rigidbody();
	PlayerMovement2* playerMovement = new PlayerMovement2();
	AnimationController* animationController = new AnimationController;
	playerComponents->push_back(rigidBody);
	playerComponents->push_back(animationController);
	playerComponents->push_back(playerMovement);

	Animation* idleAnimation = new Animation(graphics, "Textures/SpriteSheets/Player_Idle_Anim.png");
	Animation* runAnimation = new Animation(graphics, "Textures/SpriteSheets/Player_Run_Anim.png");
	Animation* jumpAnimation = new Animation(graphics, "Textures/SpriteSheets/Player_Jump_Anim.png");
	Animation* TakeDamageAnimation = new Animation(graphics, "Textures/SpriteSheets/Player_TakeDamage_Anim.png");
	Animation* AttackAnimation = new Animation(graphics, "Textures/SpriteSheets/Player_Attack_Anim.png");

	idleAnimation->transitionPairs = { std::make_pair([playerMovement]() {return playerMovement->running; }, runAnimation),
										std::make_pair([playerMovement]() {
	if (playerMovement->jumpAnimTrigger)
	{
		playerMovement->jumpAnimTrigger = false;
		return true;
	}
	else
	{
		return false;
	}}, jumpAnimation) };


	runAnimation->transitionPairs = { std::make_pair([playerMovement]() {return !playerMovement->running; }, idleAnimation),std::make_pair([playerMovement]() {
	if (playerMovement->jumpAnimTrigger)
	{
		playerMovement->jumpAnimTrigger = false;
		return true;
	}
	else
	{
		return false;
	}}, jumpAnimation)
	};
	jumpAnimation->transitionPairs = { std::make_pair([playerMovement,rigidBody]() {return playerMovement->IsGrounded() && rigidBody->GetVelocity().y <= 0; }, idleAnimation) };
	animationController->Animations = { idleAnimation, runAnimation,jumpAnimation, TakeDamageAnimation, AttackAnimation };

	playerGO = new Entity(playerComponents);
	gameObjects.push_back(playerGO);

	playerGO->GetComponent<Transform>()->SetPosition(levelReader->playerSpawnPos);
}


