#pragma once
#include "Component.h"
#include"Animation.h"
#include "SpriteRenderer.h"
class AnimationController : public Component
{

public:
	void Update(float deltaTime) override;
	void CheckTransitions();
	void PlayAnimation(Animation* anim);
	void Initialize(void* owner) override;
	std::vector<Animation*> animations;
private:
	Animation* currentPlayingAnimation;
	SpriteRenderer* spriteRenderer;
};