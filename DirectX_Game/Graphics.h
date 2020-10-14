#pragma once
#include<d3d11.h>
#include "Camera.h"
#include <vector>
#include"Shaders.h"
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
		UINT nrOfVertices;
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
	ID3D11Buffer* squareIndexBuffer;

	bool Init();
	void CreateDrawable(std::vector<LevelBlockVertex> vertices,ShaderClass* shaders, ID3D11Buffer* vertexBuffer
		,UINT vertexSize,ID3D11Buffer* indexBuffer,vector<ID3D11Buffer*> vsConstantBuffers = vector<ID3D11Buffer*>()
		, vector<ID3D11ShaderResourceView*> psResourceViews = vector<ID3D11ShaderResourceView*>(), vector<ID3D11Buffer*> psConstantBuffers = vector<ID3D11Buffer*>());
	void Draw();
	void MoveCamera(float x, float y);
	void CreateConstantBuffer(ID3D11Buffer** buffer, UINT size); 
	void Update();
	void MapToBuffer(ID3D11Buffer* buffer, const void* data, size_t size);
	Graphics(HWND handle);
	Graphics();
	~Graphics();
private:
	void CreateSquareIndexBuffer();
	void InitSampler();
	HRESULT CreateDirect3DContext(HWND wndHandle);
	HWND handle;
	std::vector<DrawableStruct*> drawables;
	ID3D11SamplerState* sampler;
};