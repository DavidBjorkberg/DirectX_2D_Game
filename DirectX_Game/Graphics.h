#pragma once
#include<d3d11.h>
#include"LevelBlock.h"
class Graphics
{
public:
	struct LevelBlockVertex
	{
		float x, y, z;
	};
	ID3D11RenderTargetView* renderTargetView = nullptr;
	bool Init();
	HRESULT CreateDirect3DContext(HWND wndHandle);
	LevelBlock* CreateLevelBlock();
	void DrawBlock(ID3D11Buffer* vertexBuffer,ShaderClass* shaders);
	Graphics(HWND handle);
	Graphics();
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
private:
	HWND handle;
};