#pragma once
#include<d3d11.h>
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
class Camera
{
public:
	void UpdateViewMatrix(ID3D11DeviceContext* deviceContext);
	Matrix GetViewMatrix();
	ID3D11Buffer* GetViewProjBuffer();
	void Move(float x, float y);
	Camera();
	Camera(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
private:
	Vector3 position;
	Vector3 lookTarget;
	Matrix viewMatrix;
	Matrix projMatrix;
	Matrix viewProj;
	ID3D11Buffer* viewProjBuffer;
	ID3D11DeviceContext* deviceContext;
};