#include "Camera.h"
#include "Transform.h"
void Camera::UpdateViewMatrix()
{
	lookTarget = Vector3(position.x, position.y, 1);
	viewMatrix = XMMatrixLookAtLH(this->position, lookTarget, Vector3::Up);
	viewProj = viewMatrix * projMatrix;
	graphics->MapToBuffer(viewProjBuffer, &viewProj, sizeof(Matrix));
}
Camera::Camera(Graphics* graphics)
{
	this->graphics = graphics;
	graphics->CreateConstantBuffer(&viewProjBuffer, sizeof(Matrix));
	projMatrix = DirectX::XMMatrixOrthographicLH(20, 20, 0.1f, 1);
	position.z = -1;
}

void Camera::Update()
{
	Vector2 targetPos = entityToFollow->GetComponent<Transform>()->GetPosition();
	//test += 0.00015f;
	this->position = Vector3(0, -10, 0);
	//this->position = Vector3(targetPos.x, targetPos.y + 6, position.z);

	UpdateViewMatrix();
}

ID3D11Buffer* Camera::GetViewProjBuffer()
{
	return viewProjBuffer;
}

void Camera::SetFollowTarget(Entity* gameObjectToFollow)
{
	this->entityToFollow = gameObjectToFollow;
}
