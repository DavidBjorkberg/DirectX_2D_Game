#pragma once
#include "SimpleMath.h"
#include"LevelBlock.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include<vector>
#include<map>
using namespace DirectX::SimpleMath;
class LevelReader
{
public:
	Vector2 playerSpawnPos;
	std::vector<Vector2> tallEnemySpawnPos;
	std::vector<Vector2> shortEnemySpawnPos;

	void AddBlock(int index, int width, int height);
	void ReadLevel(const char* fileName);
	LevelReader();
	LevelReader(Graphics* graphics, std::vector<LevelBlock*>* level);
private:
	enum class PixelType
	{
		Background, Block, PlayerComponent, TallEnemy, ShortEnemy
	};
	std::map<Color, PixelType> colorTranslationPair;
	Vector2* topLeftOfWindow = new Vector2(-10.2f, 10.2f);

	unsigned char* rgb;
	int levelSizeX;
	int levelSizeY;

	ShaderClass* levelBlockShaders;
	std::vector<LevelBlock*>* levelBlocks;
	Graphics* graphics;

	int GetObjectHeight(int startIndex, PixelType type);
	int GetObjectWidth(int startIndex, PixelType type);
	void AddToRead(std::vector<unsigned int>& readVector, int startIndex, int width, int height);
	bool HasBlockAbove(Vector2 pos);
	bool HasBlockBelow(Vector2 pos);
	void CreateLevelDrawables();
	void CreateUnit(int index, PixelType type);
	PixelType GetPixelType(int index);
};