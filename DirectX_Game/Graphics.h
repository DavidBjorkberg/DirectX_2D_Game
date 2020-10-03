#pragma once
#include<d3d11.h>
#include"LevelBlock.h"
#include "Camera.h"
class Graphics
{
public:
	struct LevelBlockVertex
	{
		Vector3 pos;
	};
	ID3D11RenderTargetView* renderTargetView = nullptr;
	bool Init();
	HRESULT CreateDirect3DContext(HWND wndHandle);
	LevelBlock* CreateLevelBlock(int index, int gridSizeX, int gridSizeY);
	void DrawBlock(ID3D11Buffer* vertexBuffer,ShaderClass* shaders);
	Graphics(HWND handle);
	Graphics();
	void MoveCamera(float x, float y);
	void CreateBlockIndexBuffer();
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
private:
	HWND handle;
	Camera camera;
	ID3D11Buffer* blockIndexBuffer;
};