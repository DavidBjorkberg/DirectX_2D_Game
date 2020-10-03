#include "Camera.h"

void Camera::UpdateViewMatrix(ID3D11DeviceContext* deviceContext)
{
	Vector3 upVector = Vector3(0, 1, 0);
	lookTarget = Vector4(position.x, position.y, 1,0);
	viewMatrix = XMMatrixLookAtLH(this->position, lookTarget, upVector);
	viewProj = viewMatrix * projMatrix;
	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = deviceContext->Map(viewProjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &viewProj, sizeof(Matrix));
	deviceContext->Unmap(viewProjBuffer, 0);
}
Camera::Camera(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	desc.ByteWidth = sizeof(Matrix);
	device->CreateBuffer(&desc, NULL, &viewProjBuffer);
	this->position = Vector4(0, 0, -2,0);

	projMatrix = DirectX::XMMatrixOrthographicLH(20, 20, 0.1f, 20.0f);
	this->deviceContext = deviceContext;
	UpdateViewMatrix(deviceContext);
}

Matrix Camera::GetViewMatrix()
{
	return viewMatrix;
}

ID3D11Buffer* Camera::GetViewProjBuffer()
{
	return viewProjBuffer;
}

void Camera::Move(float x, float y)
{
	this->position += Vector4(x, y, 0,0);
	UpdateViewMatrix(deviceContext);
}

Camera::Camera()
{
}
