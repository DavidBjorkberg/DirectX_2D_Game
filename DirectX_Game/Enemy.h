#pragma once
#include"BoxCollider.h"
#include<d3d11.h>
#include"Texture.h"
#include"Graphics.h"
#include"CollisionHandler.h"
#include"Animation.h"
class Enemy
{
public:
	BoxCollider* collider;
	bool isToBeRemoved;
	bool damagedPlayer;
	void Update(Vector3 playerPos, float deltaTime, bool isPlayerAlive);
	void TakeDamage();
	int drawableIndex;
	Enemy();
	Enemy(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler);
protected:
	void Init(int enemyIndex, std::string filepath);
	float width = 2;
	float height = 2;
	float modelWidth = 0.6f;
	float modelHeight = 1.2f;
	float attackRange = 1.2f;
	float attackHeight = 1;
private:
	Texture texture;
	ShaderClass* shaders;
	CollisionHandler* collisionHandler;
	Animation* runAnimation;
	Animation* attackAnimation;
	Animation* hitAnimation;
	Animation* currentAnimation;
	BoxCollider* attackCollider;
	Vector3 previousTranslation;
	Vector3 position;
	Vector3 curVelocity;
	Graphics* graphics;
	ID3D11Buffer* moveBuffer;
	ID3D11Buffer* currentAnimationBuffer;
	ID3D11Buffer* facingDirBuffer;
	Matrix moveMatrix = Matrix::Identity;
	float detectionRange = 4;
	float gravity = 6;
	float deltaTime;
	int health = 2;
	bool isWalking = true;;
	bool facingRight = true;

	void UpdateAnimation();
	void SwitchWalkingDir();
	void ApplyGravity();
	void InitializeShaders();
	void CheckNextFrameCollision();
	void CreateDrawable();
	void Move();
	bool IsGrounded();
	void ObservePlayer(Vector3 playerPos);
	void Attack();
};