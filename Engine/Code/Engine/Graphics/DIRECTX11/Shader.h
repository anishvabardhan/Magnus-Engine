#pragma once

#if DX11_API

#include "Engine/Core/CoreIncludes.h"

#include <d3d11.h>
#include <d3dcompiler.h>

enum SHADER_TYPE
{
	VERTEX_SHADER,
	PIXEL_SHADER
};

class Shader
{
public:
	ID3DBlob* m_VSBlob = nullptr;
	ID3DBlob* m_PSBlob = nullptr;
	union
	{
		struct
		{
	        ID3D11VertexShader* m_VS;
	        ID3D11PixelShader* m_PS;
		};
	};

	Shader();
	~Shader();

	void CompileShader(SHADER_TYPE shaderType, const wchar_t* filename, const std::string& entryPoint, const std::string version);
	void CreateShaders();
	void LoadShaders();
};

#endif