#pragma once
#include <vector>
class Component
{
public:
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Initialize(void* owner);
protected:
	void* owner;
};

