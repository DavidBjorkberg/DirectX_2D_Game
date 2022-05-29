#pragma once
#include<d3d11.h>
#include"Graphics.h"
#include <map>
#include <functional>
#include "Texture.h"
#include "SpriteRenderer.h"
class Animation
{
public:
	Animation();
	Animation(Graphics* graphics,string spriteSheetPath, bool loop = true, int FPS = 5);
	void Update(float deltaTime, SpriteRenderer* spriteRenderer);
	Animation* Play(SpriteRenderer* spriteRenderer);
	std::vector <std::pair<std::function<bool()>, Animation*>> transitionPairs; 
	bool isPlaying;
	bool loop;
private:
	struct AnimationData
	{
 		int currentFrame;
	};
	AnimationData animationData;
	Graphics* graphics;
	Texture spriteSheet;
	int FPS;
	float currentFrameTimer;
};