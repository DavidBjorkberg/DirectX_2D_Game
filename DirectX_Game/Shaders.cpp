#include "Shaders.h"

bool ShaderClass::CreatePS(ID3D11Device* device, LPCWSTR fileName)
{
	return this->ps.Initialize(device, fileName);
}

bool ShaderClass::CreateVS(ID3D11Device* device, LPCWSTR shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	return this->vs.Initialize(device, shaderpath, layoutDesc, numElements);
}
//VERTEX SHADER
bool VertexShader::Initialize(ID3D11Device* device, LPCWSTR shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		shaderpath, // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"main",		// entry point
		"vs_5_0",		// shader model (target)
		D3DCOMPILE_DEBUG,	// shader compile options (DEBUGGING)
		0,				// IGNORE...DEPRECATED.
		&this->buffer,			// double pointer to ID3DBlob		
		&errorBlob		// pointer for Error Blob messages.
	);
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderpath;
		return false;
	}
	hr = device->CreateVertexShader(this->buffer->GetBufferPointer(), this->buffer->GetBufferSize(), nullptr, &shader);
	if (FAILED(hr))
	{

		std::wstring errorMsg = L"Failed to create vertex shader: ";
		errorMsg += shaderpath;
		return false;
	}

	hr = device->CreateInputLayout(layoutDesc, numElements, this->buffer->GetBufferPointer(), this->buffer->GetBufferSize(), &this->inputLayout);
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to create input layout.";
		errorMsg += shaderpath;
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
	return this->shader;
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return this->buffer;
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return this->inputLayout;
}
//PIXEL SHADER
bool PixelShader::Initialize(ID3D11Device* device, LPCWSTR shaderpath)
{
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		shaderpath, // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"main",		// entry point
		"ps_5_0",		// shader model (target)
		D3DCOMPILE_DEBUG,	// shader compile options (DEBUGGING)
		0,				// IGNORE...DEPRECATED.
		&this->buffer,			// double pointer to ID3DBlob		
		&errorBlob		// pointer for Error Blob messages.
	);
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderpath;
		return false;
	}

	hr = device->CreatePixelShader(this->buffer->GetBufferPointer(), this->buffer->GetBufferSize(), NULL, &this->shader);
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderpath;
		return false;
	}
	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return this->shader;
}


