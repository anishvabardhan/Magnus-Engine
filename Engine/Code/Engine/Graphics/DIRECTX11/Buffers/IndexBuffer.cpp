#if DX11_API

#include "IndexBuffer.h"

#include "Engine/Graphics/DIRECTX11/Renderer.h"
#include "Engine/Core/LogMessage.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Load(const void* data, unsigned int count)
{
	m_Count = count;

	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.ByteWidth = sizeof(unsigned int) * count;

	D3D11_SUBRESOURCE_DATA initData = {};
	ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
	initData.pSysMem = data;

	HRESULT result = g_Renderer->GetDevice()->CreateBuffer(&desc, &initData, &m_Buffer);

	LOG_CHECK(SUCCEEDED(result)) << "Buffer was not created!!";

#if MAGNUS_DEBUG
	const char debugName[] = "IndexBuffer";
    m_Buffer->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( debugName ),debugName );
#endif
}

void IndexBuffer::Bind()
{
	g_Renderer->GetContext()->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::Release()
{
	SAFE_RELEASE(m_Buffer)
}

#endif