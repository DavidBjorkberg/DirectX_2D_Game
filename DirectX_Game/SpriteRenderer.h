#pragma once
#include "Component.h"
#include<d3d11.h>
#include "Graphics.h"
#include"SimpleMath.h"
#include "Texture.h"
using namespace DirectX::SimpleMath;
class SpriteRenderer : public Component
{
public:
	void UpdatePositionBuffer(const void* data);
	void UpdateRotationBuffer(const void* data);
	void UpdateAnimationBuffer(const void* data);
	virtual void Initialize(void* owner) override;
	SpriteRenderer(std::string pathToSprite, int width, int height, Graphics* graphics, Vector4 minMaxUV = Vector4::Zero, std::string vertexShader = "LevelBlockVertex.hlsl", std::string pixelShader = "LevelBlockPixel.hlsl");
private:
	ID3D11Buffer* positionBuffer;
	ID3D11Buffer* rotationBuffer;
	ID3D11Buffer* animationBuffer;
	Texture sprite;
	Graphics* graphics;
	std::string pathToSprite;
	int width;
	int height;
	std::string vertexShader;
	std::string pixelShader;
	Vector4 minMaxUV;
};