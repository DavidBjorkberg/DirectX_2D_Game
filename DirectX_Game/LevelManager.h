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
	ID3D11Buffer* blockIndexBuffer;
	Graphics* graphics;
	CollisionHandler* collisionHandler;
	unsigned char* rgb;
	int gridSizeX = 5;
	int gridSizeY = 5;

	bool IsBackground(int index);
	int GetObjectHeight(int startIndex);
	int GetObjectWidth(int startIndex);
	void CreateBlockIndexBuffer();
	void AddToRead(std::vector<unsigned int>& readVector, int startIndex, int width, int height);
};