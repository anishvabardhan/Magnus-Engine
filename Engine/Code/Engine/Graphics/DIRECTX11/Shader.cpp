#include "Engine/Core/EngineCommon.h"
#if DX11_API

#include "Shader.h"

#include "Renderer.h"

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

Shader::Shader()
{
	CompileShader(VERTEX_SHADER, MAGNUS_VERTEX_SHADER, "vsmain", MAGNUS_VERTEX_SHADER_VER);
	CompileShader(PIXEL_SHADER, MAGNUS_PIXEL_SHADER, "psmain", MAGNUS_PIXEL_SHADER_VER);

	CreateShaders();

	LoadShaders();
}

Shader::~Shader()
{
	SAFE_RELEASE(m_VS)
	SAFE_RELEASE(m_PS)
	SAFE_RELEASE(m_VSBlob)
	SAFE_RELEASE(m_PSBlob)
}

void Shader::CompileShader(SHADER_TYPE shaderType, const wchar_t* filename, const std::string& entryPoint, const std::string version)
{
	if(shaderType == SHADER_TYPE::VERTEX_SHADER)
	{
		D3DCompileFromFile(
		filename, 
		0, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		entryPoint.c_str(), 
		version.c_str(), 
		0, 
		0, 
		&m_VSBlob, 
		nullptr
	    );
	}
	else if(shaderType == SHADER_TYPE::PIXEL_SHADER)
	{
		D3DCompileFromFile(
		filename, 
		0, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		entryPoint.c_str(), 
		version.c_str(), 
		0, 
		0, 
		&m_PSBlob, 
		nullptr
	    );
	}
}

void Shader::CreateShaders()
{
	g_Renderer->GetDevice()->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize(), nullptr, &m_VS);
	g_Renderer->GetDevice()->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize(), nullptr, &m_PS);

#if MAGNUS_DEBUG
	const char vertexDebugName[] = "VertexShader";
    m_VS->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( vertexDebugName ),vertexDebugName );
	
	const char pixelDebugName[] = "PixelShader";
    m_PS->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( pixelDebugName ),pixelDebugName );
#endif
}

void Shader::LoadShaders()
{
	g_Renderer->GetContext()->VSSetShader(m_VS, nullptr, 0);
	g_Renderer->GetContext()->PSSetShader(m_PS, nullptr, 0);
}

#endif