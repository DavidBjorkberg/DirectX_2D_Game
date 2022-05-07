#include "SpriteRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"
#include "Game.h"
void SpriteRenderer::UpdatePositionBuffer(const void* data)
{
	this->graphics->MapToBuffer(positionBuffer, data, sizeof(DirectX::SimpleMath::Matrix));
}

void SpriteRenderer::UpdateRotationBuffer(const void* data)
{
	this->graphics->MapToBuffer(rotationBuffer, data, 16);
}

void SpriteRenderer::UpdateAnimationBuffer(const void* data)
{
	this->graphics->MapToBuffer(animationBuffer, data, 16);
}

void SpriteRenderer::Initialize(void* owner)
{
	sprite.Initialize(graphics->device, graphics->deviceContext, pathToSprite);

	vector<ID3D11Buffer*> vsConstantBuffers;
	vsConstantBuffers.push_back(Game::GetMainCamera()->GetViewProjBuffer());
	vsConstantBuffers.push_back(positionBuffer);
	//vsConstantBuffers.push_back(animationBuffer);
	//vsConstantBuffers.push_back(rotationBuffer);
	vector<ID3D11ShaderResourceView*> psResourceViews;
	psResourceViews.push_back(sprite.GetResourceView());

	std::vector<Graphics::Vertex> vertices;

	vertices.push_back({ Vector2(0,height)		,Vector2(minMaxUV.x,minMaxUV.z) });
	vertices.push_back({ Vector2(width,0)		,Vector2(minMaxUV.y,minMaxUV.w) });
	vertices.push_back({ Vector2(0,0)			,Vector2(minMaxUV.x,minMaxUV.w) });
	vertices.push_back({ Vector2(width,height)	,Vector2(minMaxUV.y,minMaxUV.z) });
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"UV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(inputDesc);
	ShaderClass* shaders = new ShaderClass();
	std::wstring stemp = std::wstring(vertexShader.begin(), vertexShader.end());
	shaders->CreateVS(graphics->device, stemp.c_str(), inputDesc, numElements);
	stemp = std::wstring(pixelShader.begin(), pixelShader.end());
	shaders->CreatePS(graphics->device, stemp.c_str());


	graphics->CreateDrawable(vertices, shaders, sizeof(Graphics::Vertex), graphics->squareIndexBuffer, vsConstantBuffers, psResourceViews);
}

SpriteRenderer::SpriteRenderer(std::string pathToSprite, int width, int height, Graphics* graphics, Vector4 minMaxUV, std::string vertexShader, std::string pixelShader)
{
	this->graphics = graphics;
	this->pathToSprite = pathToSprite;
	this->width = width;
	this->height = height;
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;
	this->minMaxUV = minMaxUV == Vector4::Zero ? Vector4(0, 1, 0, 1) : minMaxUV;
	graphics->CreateConstantBuffer(&positionBuffer, sizeof(DirectX::SimpleMath::Matrix));
	graphics->CreateConstantBuffer(&rotationBuffer, 16);
	graphics->CreateConstantBuffer(&animationBuffer, 16);
}
