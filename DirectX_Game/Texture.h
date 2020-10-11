#pragma once
#include<d3d11.h>
#include<string>
class Texture
{
public:
	Texture();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string fileName);
	ID3D11Texture2D* GetTexture();
	ID3D11ShaderResourceView* GetResourceView();
private:
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureView;
};