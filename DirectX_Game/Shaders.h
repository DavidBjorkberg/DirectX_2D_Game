#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
class VertexShader
{
public:
	bool Initialize(ID3D11Device* device, LPCWSTR shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	ID3D11InputLayout* GetInputLayout();
private:
	ID3D11VertexShader* shader;
	ID3D10Blob* buffer;
	ID3D11InputLayout* inputLayout;
};

class PixelShader
{
public:
	bool Initialize(ID3D11Device* device, LPCWSTR shaderpath);
	ID3D11PixelShader* GetShader();
private:
	ID3D11PixelShader* shader;
	ID3D10Blob* buffer;
};
class ShaderClass
{
public:
	VertexShader vs;
	PixelShader ps;
	bool CreatePS(ID3D11Device* device, LPCWSTR fileName);
	bool CreateVS(ID3D11Device* device, LPCWSTR shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
};