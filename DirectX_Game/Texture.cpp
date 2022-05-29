#include "Texture.h"
#include "stb_image.h"
#include"ScreenGrab.h"
#include <wrl/client.h>
#include<wincodec.h>
Texture::Texture()
{
}

Texture::~Texture()
{
	delete texture;
	delete textureView;
}

void Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string fileName)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Height = 556;
	textureDesc.Width = 567;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* tex = nullptr;
	ID3D11Resource* res;
	 device->CreateTexture2D(&textureDesc, NULL, &tex);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(tex, &srvDesc, &textureView);
	std::wstring file = std::wstring(fileName.begin(), fileName.end());
	LPCWSTR finalPath = file.c_str();
	
	HRESULT hr = DirectX::CreateWICTextureFromFile(device, finalPath, &res, &textureView);
}
ID3D11ShaderResourceView* Texture::GetResourceView()
{
	return textureView;
}
