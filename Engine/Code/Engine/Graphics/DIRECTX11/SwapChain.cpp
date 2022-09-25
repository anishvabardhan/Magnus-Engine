﻿#include "Renderer.h"
#if DX11_API

#include "SwapChain.h"

#include "Texture.h"

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
	SAFE_DELETE_POINTER(m_BackBuffer)
	SAFE_RELEASE(m_DeviceSwapChain)
}

void SwapChain::PostInitialise()
{
	ID3D11Texture2D* textureHandle = nullptr;
	m_DeviceSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&textureHandle);

	m_BackBuffer = new Texture(textureHandle);
}

void SwapChain::Present(bool vsync)
{
	if(vsync)
		m_DeviceSwapChain->Present(1, 0);
	else
		m_DeviceSwapChain->Present(0, 0);
}

Texture* SwapChain::GetBackBuffer() const
{
	return m_BackBuffer;
}

#endif