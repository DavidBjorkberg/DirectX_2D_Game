#include "LevelManager.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

void LevelManager::AddBlock(int index, int width, int height)
{
	Vector3 topLeftOfWindow = Vector3(-10.2f, 10.2f, 0);
	int row = floor((float)index / (float)gridSizeX);
	int column = index % gridSizeX;
		
	Vector3 bottomLeftOfBlock = topLeftOfWindow + Vector3(column, -row -height, 0);
	Graphics::LevelBlockVertex vertices[4] =
	{
		bottomLeftOfBlock + Vector3(0,height,0),
		Vector2(0, 0),
		bottomLeftOfBlock + Vector3(width,0,0),
		Vector2(1, 1),
		bottomLeftOfBlock,
		Vector2(0, 1),
		bottomLeftOfBlock + Vector3(width,height,0),
		Vector2(1, 0)
	};

	LevelBlock* newBlock = new LevelBlock(bottomLeftOfBlock, width, height);
	this->level.push_back(newBlock);

	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(graphics->camera.GetViewProjBuffer());

	graphics->CreateDrawable(vertices,sizeof(vertices), levelBlockShaders, newBlock->vertexBuffer
		, sizeof(Graphics::LevelBlockVertex)
		, blockIndexBuffer, vsConstantBuffers);

	this->collisionHandler->AddCollider(level[level.size() - 1]->collider);
}
void LevelManager::CreateBlockIndexBuffer()
{
	DWORD indices[] = {
	0,  1,  2,
	0,  3,  1,
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 6;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData;

	indexData.pSysMem = indices;
	graphics->device->CreateBuffer(&indexBufferDesc, &indexData, &blockIndexBuffer);
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

LevelManager::LevelManager(Graphics* graphics, CollisionHandler* collisionHandler)
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		//{"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	levelBlockShaders = new ShaderClass();
	levelBlockShaders->CreatePS(graphics->device, L"LevelBlockPixel.hlsl");
	levelBlockShaders->CreateVS(graphics->device, L"LevelBlockVertex.hlsl", inputDesc, numElements);
	this->graphics = graphics;
	this->collisionHandler = collisionHandler;
	CreateBlockIndexBuffer();
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
