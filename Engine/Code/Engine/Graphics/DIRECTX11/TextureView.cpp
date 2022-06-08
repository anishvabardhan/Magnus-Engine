#include "Renderer.h"
#include "Texture.h"

#if DX11_API

#include "TextureView.h"

TextureView::TextureView(Texture* textureHandle)
	: m_TextureHandle(textureHandle)
{
}

TextureView::~TextureView()
{
	SAFE_RELEASE(m_RTV)
	SAFE_DELETE_POINTER(m_TextureHandle)
}

void TextureView::CreateRenderTargetView()
{
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
    renderTargetViewDesc.Format = m_TextureHandle->m_Desc.Format;

    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;

	g_Renderer->GetDevice()->CreateRenderTargetView(m_TextureHandle->m_Handle, &renderTargetViewDesc, &m_RTV);
}

void TextureView::SetRenderTarget()
{
	g_Renderer->GetContext()->OMSetRenderTargets(1, &m_RTV, nullptr);
}

#endif