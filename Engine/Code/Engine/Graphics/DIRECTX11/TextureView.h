#pragma once

#if DX11_API

#include <d3d11.h>

class Texture;

class TextureView
{
	Texture* m_TextureHandle = nullptr;

	ID3D11RenderTargetView* m_RTV = nullptr;
public:
	friend class Renderer;

	TextureView(Texture* textureHandle);
	~TextureView();

	void CreateRenderTargetView();
	void SetRenderTarget();
};

#endif