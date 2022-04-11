#pragma once

#if DX11_API

#include "Engine/Core/CoreIncludes.h"

#include <d3d11.h>
#include <d3dcompiler.h>

class VertexShader
{
	ID3D11VertexShader* m_VS = nullptr;
public:
	ID3DBlob* m_Blob = nullptr;

	VertexShader();
	~VertexShader();

	void CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version);
	void CreateShader();
	void LoadShader();
};

class PixelShader
{
	ID3D11PixelShader* m_PS = nullptr;
public:
	ID3DBlob* m_Blob = nullptr;

	PixelShader();
	~PixelShader();

	void CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version);
	void CreateShader();
	void LoadShader();
};

class Shader
{
	//union
	//{
	//	struct
	//	{
	//        ID3D11VertexShader* m_VS = nullptr;
	//        ID3D11PixelShader* m_PS = nullptr;
	//		ID3DBlob* m_Blob = nullptr;
	//	};
	//};
public:
	Shader();
	~Shader();

	void CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version);
	void CreateShaders();
	void LoadShaders();
};
#endif