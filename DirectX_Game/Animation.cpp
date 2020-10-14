#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(Graphics* graphics, AnimationType animationType)
{
	this->graphics = graphics;
	this->animationType = animationType;
	if (animationType == AnimationType::Attack)
	{
		animationData.startFrameY = 0;
	}
	else if (animationType == AnimationType::Idle)
	{
		animationData.startFrameY = 1;
	}
	else if (animationType == AnimationType::Jump)
	{
		animationData.startFrameY = 2;
	}
	else if (animationType == AnimationType::Run)
	{
		animationData.startFrameY = 3;
	}
	animationData.currentFrame = 0;
	FPS = 5;
	currentFrameTimer = 0;
}

void Animation::Update(float deltaTime,ID3D11Buffer* animationBuffer)
{
	currentFrameTimer += deltaTime;
	if (isPlaying && currentFrameTimer >= 1.0f / FPS)
	{
		if (animationData.currentFrame >= 7)
		{
			isPlaying = false;
			currentFrameTimer = 0;
			animationData.currentFrame = 0;
		}
		else
		{
			currentFrameTimer = 0;
			animationData.currentFrame++;
			graphics->MapToBuffer(animationBuffer, &animationData, sizeof(AnimationData));
		}
	}
}

Animation* Animation::Play(ID3D11Buffer* animationBuffer)
{
	isPlaying = true;
	graphics->MapToBuffer(animationBuffer, &animationData, sizeof(AnimationData));
	return this;
}
