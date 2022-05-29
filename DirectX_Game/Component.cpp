#include "Component.h"
void Component::Update(float deltaTime)
{
}

void Component::LateUpdate(float deltaTime)
{
}

void Component::Initialize(void* owner)
{
	this->owner = owner;

}

void* Component::GetOwner()
{
	return owner;
}

Component::Component()
{
}

Component::~Component()
{
}
