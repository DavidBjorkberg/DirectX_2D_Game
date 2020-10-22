#include "Camera.h"

void Camera::UpdateViewMatrix()
{
	lookTarget = Vector3(position.x, position.y, 1);
	viewMatrix = XMMatrixLookAtLH(this->position, lookTarget, Vector3::Up);
	viewProj = viewMatrix * projMatrix;
	
	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = deviceContext->Map(viewProjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &viewProj, sizeof(Matrix));
	deviceContext->Unmap(viewProjBuffer, 0);
}
Camera::Camera(ID3D11DeviceContext* deviceContext)
{
	this->deviceContext = deviceContext;
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
	this->position += Vector3(x, y, 0);
	worldMatrix = Matrix::CreateTranslation(position);

	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = deviceContext->Map(worldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &worldMatrix, sizeof(Matrix));
	deviceContext->Unmap(worldBuffer, 0);
	UpdateViewMatrix();
}

void Camera::Init(Vector3 playerPos)
{
	this->position = Vector3(playerPos.x, playerPos.y, -1);
	projMatrix = DirectX::XMMatrixOrthographicLH(20,20, 0.1f, 20.0f);
	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	HRESULT hr = deviceContext->Map(worldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &worldMatrix, sizeof(Matrix));
	deviceContext->Unmap(worldBuffer, 0);
	UpdateViewMatrix();
}

Camera::Camera()
{
}
