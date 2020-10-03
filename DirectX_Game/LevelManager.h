#pragma once
#include<vector>
#include"LevelBlock.h"
#include"Graphics.h"
class LevelManager
{
public:
	struct LevelBlockVertex
	{
		float x, y, z;
	};
	std::vector<LevelBlock*> level;
	void AddBlock();
	void CreateLevel();
	void DrawLevel(ID3D11DeviceContext* deviceContext);
	ShaderClass levelShaders;
	LevelManager();
	LevelManager(Graphics* graphics);
private:
	Graphics* graphics;
};