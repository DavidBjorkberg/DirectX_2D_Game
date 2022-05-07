#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(Graphics* graphics, AnimationType animationType, bool loop, int FPS)
{
	this->graphics = graphics;
	this->animationType = animationType;
	this->FPS = FPS;
	this->loop = loop;
	animationData.currentFrame = 0;
	currentFrameTimer = 0;
	animationData.startFrameY = (int)animationType;
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

Animation* Animation::Play(ID3D11Buffer* animationBuffer)
{
	isPlaying = true;
	currentFrameTimer = 0;
	animationData.currentFrame = 0;
	graphics->MapToBuffer(animationBuffer, &animationData, sizeof(AnimationData));
	return this;
}
