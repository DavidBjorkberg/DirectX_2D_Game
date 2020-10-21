#pragma once
#include<d3d11.h>
#include"Graphics.h"
class Animation
{
public:
	enum class AnimationType
	{
		Attack, Death, Hit, Idle, Jump, Run,
	};
	Animation* Play(ID3D11Buffer* animationBuffer, Animation* currentAnimation);
	bool isPlaying;
	bool loop;
	AnimationType animationType;

	void Update(float deltaTime, ID3D11Buffer* animationBuffer);
	Animation();
	Animation(Graphics* graphics, AnimationType animationType, bool loop = true, int FPS = 5);
private:
	struct AnimationData
	{
		int startFrameY;
		int currentFrame;
	};
	AnimationData animationData;
	Graphics* graphics;
	int FPS;
	float currentFrameTimer;
};