#if DX11_API

#include "VertexBuffer.h"

#include "Engine/Graphics/DIRECTX11/Renderer.h"
#include "Engine/Core/LogMessage.h"

VertexBuffer::VertexBuffer()
{
	
}

VertexBuffer::~VertexBuffer()
{
	Release();
}

void VertexBuffer::Load(const void* data, uint32_t vertexSize, uint32_t arraySize, void* shaderByteCode, size_t shaderByteSize)
{
	m_VertexSize = vertexSize;

	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.ByteWidth = arraySize;

	D3D11_SUBRESOURCE_DATA initData = {};
	ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
	initData.pSysMem = data;

	HRESULT result = g_Renderer->GetDevice()->CreateBuffer(&desc, &initData, &m_Buffer);

	LOG_CHECK(SUCCEEDED(result)) << "Buffer was not created!!";

	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	result = g_Renderer->GetDevice()->CreateInputLayout(layout, ARRAYSIZE(layout), shaderByteCode, shaderByteSize, &m_Layout);

	LOG_CHECK(SUCCEEDED(result)) << "Layout was not created!!";
}

void VertexBuffer::Bind()
{
	const uint32_t stride = sizeof(float) * m_VertexSize;
	const uint32_t offset = 0;
	g_Renderer->GetContext()->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);

	g_Renderer->GetContext()->IASetInputLayout(m_Layout);
}

void VertexBuffer::Release()
{
	SAFE_RELEASE(m_Layout)
	SAFE_RELEASE(m_Buffer)
}

#endif