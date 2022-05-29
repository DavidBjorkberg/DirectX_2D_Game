#include "AnimationController.h"
#include "Entity.h"
void AnimationController::Update(float deltaTime)
{
	CurrentPlayingAnimation->Update(deltaTime, SpriteRenderer);
	CheckTransitions();
}

void AnimationController::CheckTransitions()
{
	for (int i = 0; i < CurrentPlayingAnimation->transitionPairs.size(); i++)
	{
		if (CurrentPlayingAnimation->transitionPairs[i].first())
		{
			PlayAnimation(CurrentPlayingAnimation->transitionPairs[i].second);
			break;
		}
	}
}

void AnimationController::PlayAnimation(Animation* anim)
{
	CurrentPlayingAnimation = anim;
	anim->Play(SpriteRenderer);
}

void AnimationController::Initialize(void* owner)
{
	Component::Initialize(owner);
	this->SpriteRenderer = static_cast<Entity*>(owner)->GetComponent<SpriteRenderer>();
	assert(Animations.size() > 0);
	PlayAnimation(Animations[0]);
}

AnimationController::AnimationController()
{
}

AnimationController::~AnimationController()
{
	for (int i = 0; i < Animations.size(); i++)
	{
		delete Animations[i];
	}
}


