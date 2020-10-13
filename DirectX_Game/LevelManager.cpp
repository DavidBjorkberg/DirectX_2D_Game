#include "LevelManager.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

void LevelManager::AddBlock(int index, int width, int height)
{
	int row = floor((float)index / (float)gridSizeX);
	int column = index % gridSizeX;
	Vector3 bottomLeftOfBlock = topLeftOfWindow + Vector3(column, -row - height, 0);

	LevelBlock* newBlock = new LevelBlock(bottomLeftOfBlock, width, height, graphics);
	this->level.push_back(newBlock);

	this->collisionHandler->AddCollider(level[level.size() - 1]->collider);
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
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	levelBlockShaders = new ShaderClass();
	levelBlockShaders->CreatePS(graphics->device, L"LevelBlockPixel.hlsl");
	levelBlockShaders->CreateVS(graphics->device, L"LevelBlockVertex.hlsl", inputDesc, numElements);
	this->graphics = graphics;
	this->collisionHandler = collisionHandler;
	ReadLevel("Textures/Level.png");
	CreateLevelDrawables();
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
bool LevelManager::HasBlockAbove(Vector3 pos)
{
	for (int i = 0; i < level.size(); i++)
	{
		Vector3 otherBottomLeft = level[i]->position;
		Vector3 otherTopRight = otherBottomLeft + Vector3(level[i]->dimensions.width-1, level[i]->dimensions.height-1, 0);
		float xMax = otherTopRight.x;
		float yMax = otherTopRight.y;
		float xMin = otherBottomLeft.x;
		float yMin = otherBottomLeft.y;

		if (pos.x <= xMax && pos.x >= xMin
			&& pos.y + 1 <= yMax && pos.y + 1 >= yMin)
		{
			return true;
		}
	}
	return false;
}

bool LevelManager::HasBlockBelow(Vector3 pos)
{

	for (int i = 0; i < level.size(); i++)
	{
		Vector3 otherBottomLeft = level[i]->position;
		Vector3 otherTopRight = otherBottomLeft + Vector3(level[i]->dimensions.width, level[i]->dimensions.height, 0);
		float xMax = otherTopRight.x;
		float yMax = otherTopRight.y;
		float xMin = otherBottomLeft.x;
		float yMin = otherBottomLeft.y;

		if (pos.x <= xMax && pos.x >= xMin
			&& pos.y - 1 <= yMax && pos.y - 1 >= yMin)
		{
			return true;
		}
	}
	return false;
}

void LevelManager::CreateLevelDrawables()
{
	std::vector<Graphics::LevelBlockVertex> vertices;
	Vector3 currentPos;
	for (int i = 0; i < level.size(); i++)
	{
		for (int j = 0; j < level[i]->dimensions.height; j++)
		{
			for (int k = 0; k < level[i]->dimensions.width; k++)
			{
				currentPos = level[i]->position + Vector3(k, j, 0);
				float u1;
				float u2;
				float v1;
				float v2;
				if (k == 0)
				{
					u1 = 0;
					u2 = 0.33f;
				}
				else if (k == level[i]->dimensions.width - 1)
				{
					u1 = 0.66f;
					u2 = 1;
				}
				else
				{
					u1 = 0.33f;
					u2 = 0.66f;
				}

				if (j == 0)
				{
					if (HasBlockBelow(currentPos))
					{
						v1 = 0.33f;
						v2 = 0.66f;
					}
					else
					{
						v1 = 0.66f;
						v2 = 1;
					}
				}
				else if (j == level[i]->dimensions.height - 1)
				{
					if (HasBlockAbove(currentPos))
					{
						v1 = 0.33f;
						v2 = 0.66f;
					}
					else
					{
						v1 = 0;
						v2 = 0.33f;
					}
				}
				else
				{
					v1 = 0.33f;
					v2 = 0.66f;
				}
				vertices.push_back({ currentPos					,Vector2(u1,v2) });
				vertices.push_back({ currentPos + Vector3(0,1,0),Vector2(u1,v1) });
				vertices.push_back({ currentPos + Vector3(1,1,0),Vector2(u2,v1) });
				vertices.push_back({ currentPos					,Vector2(u1,v2) });
				vertices.push_back({ currentPos + Vector3(1,1,0),Vector2(u2,v1) });
				vertices.push_back({ currentPos + Vector3(1,0,0),Vector2(u2,v2) });

			}
		}
		vector<ID3D11Buffer*> vsConstantBuffers;
		vsConstantBuffers.push_back(graphics->camera.GetViewProjBuffer());

		vector<ID3D11ShaderResourceView*> psResourceViews;
		psResourceViews.push_back(level[i]->texture.GetResourceView());

		vector<ID3D11Buffer*> psConstantBuffer;
		psConstantBuffer.push_back(level[i]->dimensionsBuffer);


		graphics->CreateDrawable(vertices, levelBlockShaders, level[i]->vertexBuffer
			, sizeof(Graphics::LevelBlockVertex)
			, nullptr, vsConstantBuffers, psResourceViews, psConstantBuffer);

	}
}
