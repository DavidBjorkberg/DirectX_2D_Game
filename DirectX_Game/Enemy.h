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
	ID3D11Buffer* vertexBuffer;
	void Update(float deltaTime);
	Enemy();
	Enemy(Vector3 pos, Graphics* graphics, CollisionHandler* collisionHandler);
private:
	Texture texture;
	ShaderClass* shaders;
	CollisionHandler* collisionHandler;
	Animation* runAnimation;
	Animation* attackAnimation;
	Animation* currentAnimation;

	Vector3 previousTranslation;
	Vector3 position;
	Vector3 curVelocity;
	Graphics* graphics;
	ID3D11Buffer* moveBuffer;
	ID3D11Buffer* currentAnimationBuffer;
	ID3D11Buffer* facingDirBuffer;
	Matrix moveMatrix = Matrix::Identity;
	float width = 2;
	float height = 2;
	float modelWidth = 0.6f;
	float modelHeight = 1.2f;
	float gravity = 6;
	float deltaTime;
	bool facingRight = true;

	void UpdateAnimation();
	void SwitchWalkingDir();
	void ApplyGravity();
	void InitializeShaders();
	void CheckNextFrameCollision();
	void CreateDrawable();
	void Move();
	bool IsGrounded();

};