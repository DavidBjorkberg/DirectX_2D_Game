#pragma once
#include<vector>
#include"LevelBlock.h"
#include"Graphics.h"
#include "stb_image.h"
#include"CollisionHandler.h"
#define STB_IMAGE_IMPLEMENTATION
class LevelManager
{
public:
	std::vector<LevelBlock*> level;
	ShaderClass* levelBlockShaders;

	void AddBlock(int index, int width, int height);
	void ReadLevel(const char* fileName);

	LevelManager();
	LevelManager(Graphics* graphics,CollisionHandler* collisionHandler);
private:
	Graphics* graphics;
	CollisionHandler* collisionHandler;
	unsigned char* rgb;
	int gridSizeX = 5;
	int gridSizeY = 5;

	Vector3 topLeftOfWindow = Vector3(-10.2f, 10.2f, 0);
	bool IsBackground(int index);
	int GetObjectHeight(int startIndex);
	int GetObjectWidth(int startIndex);
	void AddToRead(std::vector<unsigned int>& readVector, int startIndex, int width, int height);
	bool HasBlockAbove(Vector3 pos);
	bool HasBlockBelow(Vector3 pos);
	void CreateLevelDrawables();
};