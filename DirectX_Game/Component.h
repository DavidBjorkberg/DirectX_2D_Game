#pragma once
#include <vector>
class Component
{
public:
	Component();
	virtual ~Component();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Initialize(void* owner);
	void* GetOwner();
protected:
	void* owner;
};

