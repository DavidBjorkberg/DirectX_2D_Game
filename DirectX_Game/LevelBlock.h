#pragma once
#include"Shaders.h"

class LevelBlock
{
public:
	LevelBlock();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* vertexBuffer;
private:
};