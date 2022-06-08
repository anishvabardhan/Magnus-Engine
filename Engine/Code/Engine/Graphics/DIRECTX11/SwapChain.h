#pragma once

#if DX11_API

#include <d3d11.h>

class Texture;

class SwapChain
{
	Texture* m_BackBuffer = nullptr;
public:
	IDXGISwapChain* m_DeviceSwapChain = nullptr;
public:
	SwapChain();
	~SwapChain();

	void PostInitialise();
	void Present(int vsync);
	Texture* GetBackBuffer() const;
};

#endif