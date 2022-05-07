#pragma once
#include"SimpleMath.h"
#include"Keyboard.h"
#include "Texture.h"
#include"Animation.h"
#include "PlayerMovement.h"
using namespace DirectX::SimpleMath;
class Player
{
public:
	ID3D11Buffer* healthBuffer;
	PlayerMovement* playerMovement;
	float maxHealth = 5;
	float currentHealth;
	float healthPercent;
	void TakeDamage();
	std::vector<int> GetEnemyHitIndices();
	void UpdateAnimation();
	void Update(float deltaTime);
	bool IsAlive();
	Player(Vector3 pos, Graphics* graphics);
	Player();

private:
	Animation* jumpAnimation;
	Animation* idleAnimation;
	Animation* runAnimation;
	Animation* attackAnimation;
	Animation* hitAnimation;
	Animation* deathAnimation;
	std::unique_ptr<DirectX::Keyboard> keyboard;
	Texture texture;
	ShaderClass* shaders;
	Graphics* graphics;
	Animation* currentAnimation;
	ID3D11Buffer* currentAnimationBuffer;

	std::vector<int> hitEnemyIndices;
	float width = 2;
	float height = 2;
	float deltaTime;
	void Attack();
	void InitializeShaders();
	void CreateDrawable(Vector3 position);
};