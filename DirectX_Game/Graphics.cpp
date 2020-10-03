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

	CreateBlockIndexBuffer();

	return true;
}

Graphics::Graphics(HWND handle)
{
	this->handle = handle;
	Init();
	camera = Camera(device, deviceContext);
}

Graphics::Graphics()
{
}
void Graphics::MoveCamera(float x, float y)
{
	camera.Move(x, y);
}
void Graphics::CreateBlockIndexBuffer()
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
	device->CreateBuffer(&indexBufferDesc, &indexData, &blockIndexBuffer);
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

LevelBlock* Graphics::CreateLevelBlock(int index, int gridSizeX, int gridSizeY)
{
	int cellSize = 1;
	int row = floor((float)index / (float)gridSizeY);
	int column = index % gridSizeX;
	LevelBlock* newBlock = new LevelBlock();
	//Top-left: -10.2f, 12.7f
	Vector3 topLeft = Vector3(-10.2f, 10.2f, 0);
	LevelBlockVertex vertices[4] =
	{
		topLeft + Vector3(cellSize * column, -cellSize * row,0),
		topLeft + Vector3(cellSize * column + cellSize, -cellSize * row - cellSize,0),
		topLeft + Vector3(cellSize * column,-cellSize * row - cellSize,0),
		topLeft + Vector3(cellSize * column + cellSize, -cellSize * row,0)
	};		

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices;
	device->CreateBuffer(&bufferDesc, &data, &newBlock->vertexBuffer);
	return newBlock;
}

void Graphics::DrawBlock(ID3D11Buffer* vertexBuffer, ShaderClass* shaders)
{
	deviceContext->VSSetShader(shaders->vs.GetShader(), nullptr, 0);
	deviceContext->GSSetShader(nullptr, nullptr, 0);
	deviceContext->HSSetShader(nullptr, nullptr, 0);
	deviceContext->DSSetShader(nullptr, nullptr, 0);
	deviceContext->PSSetShader(shaders->ps.GetShader(), nullptr, 0);

	ID3D11Buffer* viewProjBuffer = camera.GetViewProjBuffer();
	deviceContext->VSSetConstantBuffers(0, 1, &viewProjBuffer);

	deviceContext->IASetInputLayout(shaders->vs.GetInputLayout());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT32 offset = 0;
	UINT32 vertexSize = sizeof(LevelBlockVertex);

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexSize, &offset);
	deviceContext->IASetIndexBuffer(blockIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->DrawIndexed(6, 0,0);
}
