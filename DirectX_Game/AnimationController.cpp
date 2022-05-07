#include "AnimationController.h"
void AnimationController::Update(float deltaTime)
{
	//currentPlayingAnimation->Update(deltaTime);
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
	anim->Play(animationBuffer);
}


