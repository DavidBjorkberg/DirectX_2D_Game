#pragma once
#include<d3d11.h>
#include"Graphics.h"
class Animation
{
public:
	enum class AnimationType
	{
		Attack, Idle, Jump, Run
	};
	Animation* Play(ID3D11Buffer* animationBuffer);
	bool isPlaying;
	AnimationType animationType;

	void Update(float deltaTime, ID3D11Buffer* animationBuffer);
	Animation();
	Animation(Graphics* graphics, AnimationType animationType);
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