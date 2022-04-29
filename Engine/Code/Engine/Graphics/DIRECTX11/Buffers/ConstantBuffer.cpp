#include "Engine/Core/LogMessage.h"

#if DX11_API

#include "ConstantBuffer.h"
#include "Engine/Graphics/DIRECTX11/Renderer.h"

ConstantBuffer* g_CBO = nullptr;

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	Release();
}

void ConstantBuffer::Init(size_t dataByteSize)
{
	m_DataByteSize = dataByteSize;

	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<unsigned int>(m_DataByteSize);
	desc.StructureByteStride = 0u;
	
	HRESULT result = g_Renderer->GetDevice()->CreateBuffer(&desc, 0, &m_Buffer);

	LOG_CHECK(SUCCEEDED(result)) << "Buffer was not created!!";
}

void ConstantBuffer::Map(const void* data)
{
	D3D11_MAPPED_SUBRESOURCE map;
	HRESULT result = g_Renderer->GetContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	
	LOG_CHECK(SUCCEEDED(result)) << "Couldn't map the constant buffer!!";
	
	memcpy(map.pData, data, m_DataByteSize);
}

void ConstantBuffer::Unmap()
{
	g_Renderer->GetContext()->Unmap(m_Buffer, 0);
}

void ConstantBuffer::Bind(unsigned int slot)
{
	g_Renderer->GetContext()->VSSetConstantBuffers(slot, 1, &m_Buffer);
}

void ConstantBuffer::Release()
{
	SAFE_RELEASE(m_Buffer)
}

#endif