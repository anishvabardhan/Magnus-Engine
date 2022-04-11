#include "Engine/Core/EngineCommon.h"
#if DX11_API

#include "Shader.h"

#include "Renderer.h"

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version)
{
	D3DCompileFromFile(
		filename, 
		0, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		entryPoint.c_str(), 
		version.c_str(), 
		0, 
		0, 
		&m_Blob, 
		nullptr
	);
}

void VertexShader::CreateShader()
{
	g_Renderer->GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VS);
}

void VertexShader::LoadShader()
{
	g_Renderer->GetContext()->VSSetShader(m_VS, nullptr, 0);
}

PixelShader::PixelShader()
{
}

PixelShader::~PixelShader()
{
}

void PixelShader::CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version)
{
	D3DCompileFromFile(
		filename, 
		0, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		entryPoint.c_str(), 
		version.c_str(), 
		0, 
		0, 
		&m_Blob, 
		nullptr
	);
}

void PixelShader::CreateShader()
{
	g_Renderer->GetDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PS);
}

void PixelShader::LoadShader()
{
	g_Renderer->GetContext()->PSSetShader(m_PS, nullptr, 0);
}

Shader::Shader()
{
	CompileShader(MAGNUS_VERTEX_SHADER, "vsmain", MAGNUS_VERTEX_SHADER_VER);
	CompileShader(MAGNUS_PIXEL_SHADER, "psmain", MAGNUS_PIXEL_SHADER_VER);

	CreateShaders();

	LoadShaders();
}

Shader::~Shader()
{
	//SAFE_RELEASE(m_VS)
	//SAFE_RELEASE(m_PS)
	//SAFE_RELEASE(m_Blob)
}

void Shader::CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version)
{
	//D3DCompileFromFile(
	//	filename, 
	//	0, 
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, 
	//	entryPoint.c_str(), 
	//	version.c_str(), 
	//	0, 
	//	0, 
	//	&m_Blob, 
	//	nullptr
	//);
}

void Shader::CreateShaders()
{
	//g_Renderer->GetDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PS);
	//g_Renderer->GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VS);
}

void Shader::LoadShaders()
{
	//g_Renderer->GetContext()->VSSetShader(m_VS, nullptr, 0);
	//g_Renderer->GetContext()->PSSetShader(m_PS, nullptr, 0);
}

#endif