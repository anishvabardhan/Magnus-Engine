#if DX11_API

#include "Renderer.h"

#include "Engine/Window/Window.h"
#include "Engine/Core/EngineCommon.h"

Renderer* g_Renderer = nullptr;

extern Window* g_Window;

Renderer::Renderer()
{
 
}

Renderer::~Renderer()
{
 
}

void Renderer::StartUp()
{
	CreateDevice();
	CreatSwapChain();
}

void Renderer::ShutDown()
{
	SAFE_RELEASE(m_SwapChain)
	SAFE_RELEASE(m_Device)
	SAFE_RELEASE(m_Context)
}

// todo Rectify the creation of device and swapchain in a single function, define a macro for DX safe check release of the COM objects

// todo figure out a way to call the DX debug layer flag when creating the device

// todo Start creating render targets

void Renderer::CreateDevice()
{
	uint32_t deviceFlags = NULL;

#if DEBUG_LAYER
		deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	D3D11CreateDevice(
		m_DXGIAdapter, 
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL,
		deviceFlags,
		featureLevels, 
		_countof(featureLevels), 
		D3D11_SDK_VERSION, 
		&m_Device, 
		NULL, 
		&m_Context
	);
}

void Renderer::CreatSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = static_cast<uint32_t>(APEX_WINDOW_DIMS[1]);
	desc.BufferDesc.Height = static_cast<uint32_t>(APEX_WINDOW_DIMS[3]);
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = static_cast<HWND>(g_Window->GetHandle());
	desc.SampleDesc.Count = 1;
	desc.Windowed = TRUE;
	
	m_DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory);

	m_DXGIFactory->CreateSwapChain(m_Device, &desc, &m_SwapChain);
}

void Renderer::Present(UINT vsync)
{
	m_SwapChain->Present(vsync, 0);
}

void Renderer::SwappingBuffers()
{
	Present(0);
}

void Renderer::BindDefaultShader()
{
	
}

void Renderer::BindFont(const Font* font, int textureSlot)
{
	
}

void Renderer::BindTexture(const Texture* texture, int textureSlot)
{
	
}

void Renderer::SetCameraUniform(const Mat4& camera)
{
	
}

void Renderer::SetModelTranslation(const Mat4& transform)
{
	
}

void Renderer::CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next)
{
	
}

void Renderer::ClearColor(const Vec4& color) const
{
}

void Renderer::Drawtext(const Vec2& position, const Vec4& color, const String& asciiText, float quadHeight, Font* font)
{
	
}

void Renderer::DrawAABB2(const AABB2& aabb2, const Vec4& color)
{
	
}

void Renderer::DrawHollowAABB2(const AABB2& aabb2, const float& thickness, const Vec4& color)
{
	
}

void Renderer::DrawLine(Vec2& start, Vec2& end, const float& thickness, const Vec4& color)
{
	
}

void Renderer::DrawArrow(Vec2& start, Vec2& end, const float& thickness, const Vec4& color)
{
	
}

void Renderer::DrawDisc(const Vec2& center, const float& radius, const Vec4& color)
{
	
}

void DrawRing(const Vec2& center, const float& radius, const Vec4& color)
{
	
}

void DrawMesh(Mesh* mesh)
{
	
}

#endif