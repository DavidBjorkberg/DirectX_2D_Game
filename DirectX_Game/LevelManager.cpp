#include "LevelManager.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

void LevelManager::AddBlock(int index, int width, int height)
{
	this->level.push_back(graphics->CreateLevelBlock(index, width, height, gridSizeX, gridSizeY));
}

void LevelManager::CreateLevel()
{
}

void LevelManager::DrawLevel(ID3D11DeviceContext* deviceContext)
{
	for (size_t i = 0; i < level.size(); i++)
	{
		graphics->DrawBlock(level[i]->GetVertexBuffer(), &levelBlockShaders);
	}
}

void LevelManager::ReadLevel(const char* fileName)
{
	int bpp = 0;
	rgb = stbi_load(fileName, &gridSizeX, &gridSizeY, &bpp, 3);
	int height = 0;
	int width = 0;
	std::vector<unsigned int> readIndex;
	for (int i = 0; i < gridSizeX * gridSizeY; i++)
	{
		if (std::find(readIndex.begin(), readIndex.end(), i) == readIndex.end())
		{
			if (!IsBackground(i))
			{
				height = GetObjectHeight(i);
				width = GetObjectWidth(i);
				for (int j = 1; j < height; j++)
				{
					if (GetObjectWidth(i + gridSizeX * j) != width)
					{
						height = j;
					}
				}
				AddBlock(i, width, height);
				AddToRead(readIndex, i, width, height);
			}
		}
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
	levelBlockShaders.CreatePS(graphics->device, L"LevelBlockPixel.hlsl");
	levelBlockShaders.CreateVS(graphics->device, L"LevelBlockVertex.hlsl", inputDesc, numElements);
	this->graphics = graphics;
	ReadLevel("Level.png");
}

bool LevelManager::IsBackground(int index)
{
	//Convert to RGB
	index *= 3;
	return rgb[index] == 255 && rgb[index + 1] == 255 && rgb[index + 2] == 255;
}

int LevelManager::GetObjectHeight(int startIndex)
{
	int height = 1;
	int curIndex = startIndex + gridSizeX;
	while (!IsBackground(curIndex) && curIndex < gridSizeX * gridSizeY)
	{
		height++;
		curIndex += gridSizeX;
	}
	return height;
}

int LevelManager::GetObjectWidth(int startIndex)
{
	int width = 1;
	int curIndex = startIndex + 1;
	while (!IsBackground(curIndex) && curIndex % gridSizeX > 0 && curIndex < gridSizeX * gridSizeY)
	{
		width++;
		curIndex++;
	}
	return width;
}

void LevelManager::AddToRead(std::vector<unsigned int>& readVector, int startIndex, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int curIndex = startIndex + gridSizeX * i + j;
			readVector.push_back(curIndex);
		}
	}
}
