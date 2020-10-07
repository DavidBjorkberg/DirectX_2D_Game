#include "Graphics.h"

bool Graphics::Init()
{
	CreateDirect3DContext(handle);
	HRESULT result;
	D3D11_TEXTURE2D_DESC descRenderTarget;
	descRenderTarget.Width = 768;
	descRenderTarget.Height = 768;
	descRenderTarget.MipLevels = 1;
	descRenderTarget.ArraySize = 1;
	descRenderTarget.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descRenderTarget.SampleDesc.Count = 4;
	descRenderTarget.SampleDesc.Quality = 0;
	descRenderTarget.Usage = D3D11_USAGE_DEFAULT;
	descRenderTarget.BindFlags = D3D11_BIND_RENDER_TARGET;
	descRenderTarget.CPUAccessFlags = 0;
	descRenderTarget.MiscFlags = 0;
	ID3D11Texture2D* renderTarget;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	device->CreateRenderTargetView(renderTarget, NULL, &renderTargetView);
	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	D3D11_VIEWPORT vp;
	vp.Width = 768;
	vp.Height = 768;
	vp.MinDepth = 0.0001f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &vp);


	return true;
}

Graphics::Graphics(HWND handle)
{
	this->handle = handle;
	Init();
	camera = Camera(deviceContext);
	CreateConstantBuffer(&camera.viewProjBuffer, sizeof(Matrix));
	camera.Init();
}

Graphics::Graphics()
{
}
void Graphics::MoveCamera(float x, float y)
{
	camera.Move(x, y);
}
HRESULT Graphics::CreateDirect3DContext(HWND wndHandle)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = wndHandle;                           // the window to be used
	scd.SampleDesc.Count = 1;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

	// create a device, device context and swap chain using the information in the scd struct
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		NULL,
		&deviceContext);

	return hr;
}

void Graphics::CreateDrawable(LevelBlockVertex vertices[],UINT verticesSize, ShaderClass* shaders
	, ID3D11Buffer* vertexBuffer,UINT vertexSize, ID3D11Buffer* indexBuffer, vector<ID3D11Buffer*> vsConstantBuffers
	, vector<ID3D11Buffer*> psConstantBuffers, vector<ID3D11ShaderResourceView*> psResourceViews)
{
	DrawableStruct* drawable = new DrawableStruct();
	drawable->shaders = shaders;
	drawable->vertexSize = vertexSize;
	drawable->indexBuffer = indexBuffer;
	drawable->vsConstantBuffers = vsConstantBuffers;
	drawable->psConstantBuffers = psConstantBuffers;
	drawable->psResourceViews = psResourceViews;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = verticesSize;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices;
	device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
	drawable->vertexBuffer = vertexBuffer;

	drawables.push_back(drawable);
}

void Graphics::Draw()
{
	for (int i = 0; i < drawables.size(); i++)
	{
		deviceContext->VSSetShader(drawables[i]->shaders->vs.GetShader(), nullptr, 0);
		deviceContext->PSSetShader(drawables[i]->shaders->ps.GetShader(), nullptr, 0);

		deviceContext->IASetInputLayout(drawables[i]->shaders->vs.GetInputLayout());
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		for (int j = 0; j < drawables[i]->vsConstantBuffers.size(); j++)
		{
			deviceContext->VSSetConstantBuffers(j, 1, &drawables[i]->vsConstantBuffers[j]);
		}
		for (int j = 0; j < drawables[i]->psConstantBuffers.size(); j++)
		{
			deviceContext->PSSetConstantBuffers(j, 1, &drawables[i]->psConstantBuffers[j]);
		}
		for (int j = 0; j < drawables[i]->psResourceViews.size(); j++)
		{
			deviceContext->PSSetShaderResources(j, 1, &drawables[i]->psResourceViews[j]);
		}
		UINT32 offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, &drawables[i]->vertexBuffer, &drawables[i]->vertexSize, &offset);
		deviceContext->IASetIndexBuffer(drawables[i]->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		deviceContext->DrawIndexed(6, 0, 0);
	}
}
void Graphics::CreateConstantBuffer(ID3D11Buffer** buffer, UINT size)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	desc.ByteWidth = size;
	device->CreateBuffer(&desc, NULL, buffer);
}
