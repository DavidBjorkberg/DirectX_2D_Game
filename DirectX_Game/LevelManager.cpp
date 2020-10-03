#include "LevelManager.h"

void LevelManager::AddBlock(int index)
{
	this->level.push_back(graphics->CreateLevelBlock(index, gridSizeX, gridSizeY));
}

void LevelManager::CreateLevel()
{
	AddBlock(0);
	AddBlock(1);
	AddBlock(8);
	AddBlock(14);
	AddBlock(16);

}

void LevelManager::DrawLevel(ID3D11DeviceContext* deviceContext)
{
	for (int i = 0; i < level.size(); i++)
	{
		graphics->DrawBlock(level[i]->GetVertexBuffer(), &levelShaders);
	}
}

LevelManager::LevelManager()
{
}

LevelManager::LevelManager(Graphics* graphics)
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		//{"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	levelShaders.CreatePS(graphics->device, L"LevelBlockPixel.hlsl");
	levelShaders.CreateVS(graphics->device, L"LevelBlockVertex.hlsl", inputDesc, numElements);
	this->graphics = graphics;
}
