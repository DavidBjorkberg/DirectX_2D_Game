#pragma once
#include<d3d11.h>
#include <SimpleMath.h>
#include "Graphics.h"
#include "Entity.h"

using namespace DirectX::SimpleMath;
class Camera
{
public:
	Camera(Graphics* graphics);
	virtual ~Camera();
	void UpdateViewMatrix();
	void SetFollowTarget(Entity* gameObjectToFollow);
	void Update();
	ID3D11Buffer* GetViewProjBuffer();
private:
	Vector3 position;
	Vector3 lookTarget;
	Matrix viewMatrix;
	Matrix projMatrix;
	Matrix viewProj;
	ID3D11Buffer* viewProjBuffer;
	Graphics* graphics;
	Entity* entityToFollow;
};