#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(Graphics* graphics, string spriteSheetPath, bool loop, int FPS)
{
	this->graphics = graphics;
	this->FPS = FPS;
	this->loop = loop;
	animationData.currentFrame = 0;
	currentFrameTimer = 0;
	spriteSheet.Initialize(graphics->device, graphics->deviceContext, spriteSheetPath);
}

void Animation::Update(float deltaTime, SpriteRenderer* spriteRenderer)
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
			spriteRenderer->UpdateAnimationBuffer(&animationData);
		}
	}
}

Animation* Animation::Play(SpriteRenderer* spriteRenderer)
{
	isPlaying = true;
	currentFrameTimer = 0;
	animationData.currentFrame = 0;
	spriteRenderer->UpdateAnimationBuffer(&animationData);
	spriteRenderer->SetAnimationSprite(&spriteSheet);
	return this;
}
