#pragma once
#include "Component.h"
#include"Animation.h"
class AnimationController : public Component
{

public:
	void Update(float deltaTime) override;
	void CheckTransitions();
	void PlayAnimation(Animation* anim);
private:
	Animation* currentPlayingAnimation;
	ID3D11Buffer* animationBuffer;
};