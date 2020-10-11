#include "Texture.h"
#include "stb_image.h"
Texture::Texture()
{
}

void Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string fileName)
{
	int width = 0;
	int height = 0;
	int bpp = 0;
	unsigned char* targaData = stbi_load(fileName.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	HRESULT hResult = device->CreateTexture2D(&textureDesc, NULL, &texture);

	unsigned int rowPitch = (width * 4) * sizeof(unsigned char);

	deviceContext->UpdateSubresource(texture, 0, NULL, targaData, rowPitch, 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	hResult = device->CreateShaderResourceView(texture, &srvDesc, &textureView);
}

ID3D11Texture2D* Texture::GetTexture()
{
	return texture;
}

ID3D11ShaderResourceView* Texture::GetResourceView()
{
	return textureView;
}
