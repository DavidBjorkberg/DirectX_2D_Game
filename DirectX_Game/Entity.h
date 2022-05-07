#pragma once
#include "Component.h"
#include <vector>
#include <SimpleMath.h>
class Entity
{
public:
	Entity(std::vector<Component*>* components);
	template <typename T>
	inline T* GetComponent()
	{
		for (Component* component : *components)
		{
			T* ComponentAsT = dynamic_cast<T*>(component);
			if (ComponentAsT != nullptr)
			{
				return ComponentAsT;
			}
		}
		return nullptr;
	};

	template <typename T>
	inline std::vector<T*>* GetAllComponentsOfType()
	{
		std::vector<T*>* returnList = new std::vector<T*>();
		for (Component* component : *components)
		{
			T* ComponentAsT = dynamic_cast<T*>(component);
			if (ComponentAsT != nullptr)
			{
				returnList->push_back(ComponentAsT);
			}
		}
		return returnList;
	}
	void UpdateComponents(float deltaTime);

private:
	std::vector<Component*>* components;
};
