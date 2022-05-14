#include "Entity.h"
#include "Transform.h"
Entity::Entity(std::vector<Component*>* components, std::string name)
{
	this->components = components;
	this->name = name;
	for (Component* component : *components)
	{
		component->Initialize(this);
	}
}

std::vector<Component*>* Entity::GetComponentList()
{
	return components;
}

void Entity::UpdateComponents(float deltaTime)
{
	for (Component* component : *components)
	{
		component->Update(deltaTime);
	}
}

