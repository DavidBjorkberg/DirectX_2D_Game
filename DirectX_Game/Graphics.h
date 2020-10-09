#pragma once
#include<d3d11.h>
#include"LevelBlock.h"
#include "Camera.h"
#include <vector>
using namespace std;
class Graphics
{
public:
	struct LevelBlockVertex
	{
		Vector3 pos;
		Vector2 UV;
	};
	struct DrawableStruct
	{
		ShaderClass* shaders;
		ID3D11Buffer* vertexBuffer;
		UINT vertexSize;
		ID3D11Buffer* indexBuffer;
		vector<ID3D11Buffer*> vsConstantBuffers;
		vector<ID3D11Buffer*> psConstantBuffers;
		vector<ID3D11ShaderResourceView*> psResourceViews;
	};
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	Camera camera;

	bool Init();
	void CreateDrawable(LevelBlockVertex vertices[],UINT verticesSize,ShaderClass* shaders, ID3D11Buffer* vertexBuffer
		,UINT vertexSize,ID3D11Buffer* indexBuffer,vector<ID3D11Buffer*> vsConstantBuffers = vector<ID3D11Buffer*>()
		, vector<ID3D11Buffer*> psConstantBuffers = vector<ID3D11Buffer*>(), vector<ID3D11ShaderResourceView*> psResourceViews = vector<ID3D11ShaderResourceView*>());
	void Draw();
	void MoveCamera(float x, float y);
	void CreateConstantBuffer(ID3D11Buffer** buffer, UINT size);
	Graphics(HWND handle);
	Graphics();
	~Graphics();
private:
	HRESULT CreateDirect3DContext(HWND wndHandle);
	HWND handle;
	std::vector<DrawableStruct*> drawables;
};