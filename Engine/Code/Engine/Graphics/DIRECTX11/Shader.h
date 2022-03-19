#pragma once

#if DX11_API

#include "Engine/Core/CoreIncludes.h"

#include <d3d11.h>
#include <d3dcompiler.h>

class Shader
{
public:
	ID3DBlob* m_Blob = nullptr;
public:
	Shader();
	~Shader();

	virtual void CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version) = 0;
	virtual void CreateShader() = 0;
	virtual void LoadShader() = 0;
};

class VertexShader : public Shader
{
	ID3D11VertexShader* m_VS = nullptr;
public:
	VertexShader();
	~VertexShader();

	virtual void CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version);
	virtual void CreateShader();
	virtual void LoadShader();
};

class PixelShader : public Shader
{
	ID3D11PixelShader* m_PS = nullptr;
public:
	PixelShader();
	~PixelShader();

	virtual void CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version);
	virtual void CreateShader();
	virtual void LoadShader();
};

#endif