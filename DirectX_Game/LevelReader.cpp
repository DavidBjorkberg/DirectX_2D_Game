#include "LevelReader.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
void LevelReader::AddBlock(int index, int width, int height)
{
	int row = floor((float)index / (float)levelSizeX);
	int column = index % levelSizeX;
	Vector3 bottomLeftOfBlock = *topLeftOfWindow + Vector3(column, -row - height, 0);

	LevelBlock* newBlock = new LevelBlock(bottomLeftOfBlock, width, height, graphics);
	this->levelBlocks->push_back(newBlock);

}

void LevelReader::ReadLevel(const char* fileName)
{
	int bpp = 0;
	rgb = stbi_load(fileName, &levelSizeX, &levelSizeY, &bpp, 3);
	int height = 0;
	int width = 0;
	std::vector<unsigned int> readIndex;
	for (int i = 0; i < levelSizeX * levelSizeY; i++)
	{
		if (std::find(readIndex.begin(), readIndex.end(), i) == readIndex.end())
		{
			PixelType type = GetPixelType(i);
			if (type != PixelType::Background)
			{
				if (type == PixelType::Block)
				{
					height = GetObjectHeight(i, type);
					width = GetObjectWidth(i, type);
					for (int j = 1; j < height; j++)
					{
						if (GetObjectWidth(i + levelSizeX * j, type) != width)
						{
							height = j;
						}
					}
					AddBlock(i, width, height);
				}
				else
				{
					CreateUnit(i, type);

				}
			}
			AddToRead(readIndex, i, width, height);
			width = 0;
			height = 0;
		}
	}
	CreateLevelDrawables();
}
LevelReader::LevelReader()
{

}
LevelReader::LevelReader(Graphics* graphics, std::vector<LevelBlock*>* level)
{
	this->levelBlocks = level;
	this->graphics = graphics;
	this->colorTranslationPair = {
		{  Color(255,255,255), PixelType::Background },
		{  Color(0,0,0), PixelType::Block },
		{  Color(0,255,0), PixelType::PlayerComponent },
		{  Color(255,0,0), PixelType::TallEnemy },
		{  Color(255,100,0), PixelType::ShortEnemy },
	};
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	levelBlockShaders = new ShaderClass();
	levelBlockShaders->CreatePS(graphics->device, L"LevelBlockPixel.hlsl");
	levelBlockShaders->CreateVS(graphics->device, L"LevelBlockVertex.hlsl", inputDesc, numElements);
}

int LevelReader::GetObjectHeight(int startIndex, PixelType type)
{
	int height = 1;
	int curIndex = startIndex + levelSizeX;
	while (GetPixelType(curIndex) == type
		&& curIndex < levelSizeX * levelSizeY)
	{
		height++;
		curIndex += levelSizeX;
	}
	return height;
}
int LevelReader::GetObjectWidth(int startIndex, PixelType type)
{
	int width = 1;
	int curIndex = startIndex + 1;
	while (GetPixelType(curIndex) == type
		&& curIndex % levelSizeX > 0
		&& curIndex < levelSizeX * levelSizeY)
	{
		width++;
		curIndex++;
	}
	return width;
}
void LevelReader::AddToRead(std::vector<unsigned int>& readVector, int startIndex, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int curIndex = startIndex + levelSizeX * i + j;
			readVector.push_back(curIndex);
		}
	}
}
bool LevelReader::HasBlockAbove(Vector3 pos)
{
	for (int i = 0; i < levelBlocks->size(); i++)
	{
		Vector3 otherBottomLeft = levelBlocks->at(i)->position;
		Vector3 otherTopRight = otherBottomLeft + Vector3(levelBlocks->at(i)->dimensions.width - 1, levelBlocks->at(i)->dimensions.height - 1, 0);
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
bool LevelReader::HasBlockBelow(Vector3 pos)
{

	for (int i = 0; i < levelBlocks->size(); i++)
	{
		Vector3 otherBottomLeft = levelBlocks->at(i)->position;
		Vector3 otherTopRight = otherBottomLeft + Vector3(levelBlocks->at(i)->dimensions.width, levelBlocks->at(i)->dimensions.height, 0);
		float xMax = otherTopRight.x;
		float yMax = otherTopRight.y;
		float xMin = otherBottomLeft.x;
		float yMin = otherBottomLeft.y;

		if (pos.x < xMax && pos.x >= xMin
			&& pos.y - 1 <= yMax && pos.y - 1 >= yMin)
		{
			return true;
		}
	}
	return false;
}
void LevelReader::CreateLevelDrawables()
{
	std::vector<Graphics::LevelBlockVertex> vertices;
	Vector3 currentPos;
	for (int i = 0; i < levelBlocks->size(); i++)
	{
		for (int j = 0; j < levelBlocks->at(i)->dimensions.height; j++)
		{
			for (int k = 0; k < levelBlocks->at(i)->dimensions.width; k++)
			{
				currentPos = levelBlocks->at(i)->position + Vector3(k, j, 0);
				float u1;
				float u2;
				float v1;
				float v2;
				if (k == 0)
				{
					u1 = 0;
					u2 = 0.33f;
				}
				else if (k == levelBlocks->at(i)->dimensions.width - 1)
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
				else if (j == levelBlocks->at(i)->dimensions.height - 1)
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
		psResourceViews.push_back(levelBlocks->at(i)->texture.GetResourceView());

		vector<ID3D11Buffer*> psConstantBuffer;
		psConstantBuffer.push_back(levelBlocks->at(i)->dimensionsBuffer);


		graphics->CreateDrawable(vertices, levelBlockShaders, sizeof(Graphics::LevelBlockVertex)
			, nullptr, vsConstantBuffers, psResourceViews, psConstantBuffer);

	}
}
void LevelReader::CreateUnit(int index, PixelType type)
{
	int row = floor((float)index / (float)levelSizeX);
	int column = index % levelSizeX;
	Vector3 position = *topLeftOfWindow + Vector3(column, -row, 0);
	if (type == PixelType::PlayerComponent)
	{
		playerSpawnPos = position;
	}
	else if (type == PixelType::TallEnemy)
	{
		tallEnemySpawnPos.push_back(position);
	}
	else if (type == PixelType::ShortEnemy)
	{
		shortEnemySpawnPos.push_back(position);
	}
}
LevelReader::PixelType LevelReader::GetPixelType(int index)
{
	index *= 3;
	return colorTranslationPair.at(Color(rgb[index],rgb[index+1],rgb[index+2]));
}
