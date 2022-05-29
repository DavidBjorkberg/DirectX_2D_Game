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
	position.z = 0;
}

void Camera::Update()
{
	if (entityToFollow != nullptr)
	{
		Vector2 targetPos = entityToFollow->GetComponent<Transform>()->GetPosition();
		this->position = Vector3(targetPos.x, targetPos.y, position.z);
	}
	else
	{
		this->position = Vector3(0, -10, 0);
	}

	UpdateViewMatrix();
}

Camera::~Camera()
{
}

ID3D11Buffer* Camera::GetViewProjBuffer()
{
	return viewProjBuffer;
}

void Camera::SetFollowTarget(Entity* gameObjectToFollow)
{
	this->entityToFollow = gameObjectToFollow;
}
