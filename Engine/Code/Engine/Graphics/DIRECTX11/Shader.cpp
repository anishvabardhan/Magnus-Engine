#if DX11_API

#include "Shader.h"

#include "Renderer.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_VS)
}

void VertexShader::CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version)
{
	D3DCompileFromFile(
		filename, 
		0, 
		0, 
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
	SAFE_RELEASE(m_PS)
}

void PixelShader::CompileShader(const wchar_t* filename, const std::string& entryPoint, const std::string version)
{
	D3DCompileFromFile(
		filename, 
		0, 
		0, 
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

#endif