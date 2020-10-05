#pragma once
#include<vector>
#include"LevelBlock.h"
#include"Graphics.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
class LevelManager
{
public:
	struct LevelBlockVertex
	{
		float x, y, z;
	};
	std::vector<LevelBlock*> level;
	void AddBlock(int index, int width, int height);
	void CreateLevel();
	void DrawLevel(ID3D11DeviceContext* deviceContext);
	void ReadLevel(const char* fileName);
	ShaderClass levelBlockShaders;
	LevelManager();
	LevelManager(Graphics* graphics);
private:
	Graphics* graphics;
	bool IsBackground(int index);
	int GetObjectHeight(int startIndex);
	int GetObjectWidth(int startIndex);
	void AddToRead(std::vector<unsigned int>& readVector, int startIndex, int width, int height);
	unsigned char* rgb;
	int gridSizeX = 5;
	int gridSizeY = 5;
};