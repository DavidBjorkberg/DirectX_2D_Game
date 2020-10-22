#pragma once
#include<d3d11.h>
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
class Camera
{
public:
	void UpdateViewMatrix();
	Matrix GetViewMatrix();
	ID3D11Buffer* GetViewProjBuffer();
	ID3D11Buffer* viewProjBuffer;
	ID3D11Buffer* worldBuffer;
	void Move(float x, float y);
	void Init(Vector3 playerPos);
	Camera();
	Camera(ID3D11DeviceContext* deviceContext);
private:
	Vector3 position;
	Vector3 lookTarget;
	Matrix viewMatrix;
	Matrix projMatrix;
	Matrix viewProj;
	Matrix worldMatrix = Matrix::Identity;
	ID3D11DeviceContext* deviceContext;
};