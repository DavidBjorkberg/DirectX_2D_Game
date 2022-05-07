#include "Entity.h"
#include "Transform.h"
Entity::Entity(std::vector<Component*>* components)
{
	this->components = components;
	for (Component* component : *components)
	{
		component->Initialize(this);
	}
}

void Entity::UpdateComponents(float deltaTime)
{
	for (Component* component : *components)
	{
		component->Update(deltaTime);
	}
}

