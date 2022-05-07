#pragma once
#include<d3d11.h>
#include"Graphics.h"
#include <map>
#include <functional>
class Animation
{
public:
	enum class AnimationType
	{
		Attack, Death, Hit, Idle, Jump, Run,
	};
	std::vector <std::pair<std::function<bool()>, Animation*>> transitionPairs; 
	Animation* Play(ID3D11Buffer* animationBuffer);
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