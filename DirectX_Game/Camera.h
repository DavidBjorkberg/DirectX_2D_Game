#pragma once
#include<d3d11.h>
#include <SimpleMath.h>
#include "Graphics.h"
#include "GameObject.h"

using namespace DirectX::SimpleMath;
class Camera
{
public:
	void UpdateViewMatrix();
	ID3D11Buffer* GetViewProjBuffer();
	void SetFollowTarget(Entity* gameObjectToFollow);
	Camera(Graphics* graphics);
	void Update();
private:
	float test = 0;
	Vector3 position;
	Vector3 lookTarget;
	Matrix viewMatrix;
	Matrix projMatrix;
	Matrix viewProj;
	ID3D11Buffer* viewProjBuffer;
	Graphics* graphics;
	Entity* gameObjectToFollow;
};