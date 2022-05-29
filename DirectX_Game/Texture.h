#pragma once
#include<d3d11.h>
#include <d3dcompiler.h>
#include<string>
#include <WICTextureLoader.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string fileName);
	ID3D11ShaderResourceView* GetResourceView();

private:
	ID3D11Resource* texture;
	ID3D11ShaderResourceView* textureView;
};