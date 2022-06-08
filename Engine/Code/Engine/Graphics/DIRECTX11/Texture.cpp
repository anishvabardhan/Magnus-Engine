#include "Engine/Core/LogMessage.h"
#if DX11_API

#include "Texture.h"

#include "Renderer.h"
#include "TextureView.h"

Texture::Texture(D3D11_TEXTURE2D_DESC desc)
	: m_Desc(desc)
{
	g_Renderer->GetDevice()->CreateTexture2D(&m_Desc, nullptr, &m_Handle);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    srvDesc.Format = m_Desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = 1;

	g_Renderer->GetDevice()->CreateShaderResourceView(m_Handle, &srvDesc, &m_SRV);
}

Texture::Texture(ID3D11Texture2D* handle)
	: m_Width(0), m_Height(0), m_Channels(4), m_Handle(handle)
{
}

Texture::Texture(String filePath)
	:m_FilePath(filePath), m_Width(0), m_Height(0), m_Channels(4)
{
}

Texture::~Texture()
{
	SAFE_RELEASE(m_Handle)
	SAFE_RELEASE(m_SRV)
}

void Texture::Initialise()
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width                     = m_Width;
	desc.Height                    = m_Height;
	desc.MipLevels                 = 1;
	desc.ArraySize                 = 1;
	desc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count          = 1;
	desc.SampleDesc.Quality        = 0;
	desc.Usage                     = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags                 = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA imgResourceData;
	imgResourceData.pSysMem = m_ImageData;
	imgResourceData.SysMemPitch = 4 * m_Width;

	HRESULT result = g_Renderer->GetDevice()->CreateTexture2D(&desc, &imgResourceData, &m_Handle);

	LOG_CHECK(SUCCEEDED(result)) << "Couldn't create Texture!!";

	result = g_Renderer->GetDevice()->CreateShaderResourceView(m_Handle, nullptr, &m_SRV);

	LOG_CHECK(SUCCEEDED(result)) << "Couldn't create TextureView!!";
}

void Texture::Bind(unsigned slot)
{
	g_Renderer->GetContext()->PSSetShaderResources(slot, 1, &m_SRV);
}

#endif