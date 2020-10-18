#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(Graphics* graphics, AnimationType animationType)
{
	this->graphics = graphics;
	this->animationType = animationType;
	FPS = 5;
	animationData.currentFrame = 0;
	currentFrameTimer = 0;
	if (animationType == AnimationType::Attack)
	{
		animationData.startFrameY = 0;
		FPS = 10;
		loop = false;
	}
	else if (animationType == AnimationType::Idle)
	{
		animationData.startFrameY = 1;
	}
	else if (animationType == AnimationType::Jump)
	{
		animationData.startFrameY = 2;
		loop = false;
	}
	else if (animationType == AnimationType::Run)
	{
		animationData.startFrameY = 3;
	}
}

void Animation::Update(float deltaTime, ID3D11Buffer* animationBuffer)
{
	currentFrameTimer += deltaTime;
	if (isPlaying && currentFrameTimer >= 1.0f / FPS)
	{
		if (animationData.currentFrame >= 7)
		{
			if (loop)
			{
				currentFrameTimer = 0;
				animationData.currentFrame = 0;
			}
			else
			{
				isPlaying = false;
			}
		}
		else
		{
			currentFrameTimer = 0;
			animationData.currentFrame++;
			graphics->MapToBuffer(animationBuffer, &animationData, sizeof(AnimationData));
		}
	}
}

Animation* Animation::Play(ID3D11Buffer* animationBuffer, Animation* currentAnimation)
{
	if (currentAnimation != this)
	{
		isPlaying = true;
		currentFrameTimer = 0;
		animationData.currentFrame = 0;
		graphics->MapToBuffer(animationBuffer, &animationData, sizeof(AnimationData));
	}
	return this;
}
