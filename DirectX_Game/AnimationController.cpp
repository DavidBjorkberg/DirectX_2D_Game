#include "AnimationController.h"
#include "Entity.h"
void AnimationController::Update(float deltaTime)
{
	currentPlayingAnimation->Update(deltaTime,spriteRenderer);
	CheckTransitions();
}

void AnimationController::CheckTransitions()
{
	for (int i = 0; i < currentPlayingAnimation->transitionPairs.size(); i++)
	{
		if (currentPlayingAnimation->transitionPairs[i].first())
		{
			PlayAnimation(currentPlayingAnimation->transitionPairs[i].second);
			break;
		}
	}
}

void AnimationController::PlayAnimation(Animation* anim)
{
	currentPlayingAnimation = anim;
	anim->Play(spriteRenderer);
}

void AnimationController::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->spriteRenderer = static_cast<Entity*>(owner)->GetComponent<SpriteRenderer>();
	assert(animations.size() > 0);
	PlayAnimation(animations[0]);
}


