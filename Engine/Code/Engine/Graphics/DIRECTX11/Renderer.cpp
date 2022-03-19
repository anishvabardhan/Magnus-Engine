#if DX11_API

#include "Renderer.h"

#include "Engine/Window/Window.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Core/LogMessage.h"
#include "Shader.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Engine/Graphics/MeshBuilder.h"

#define DEBUG_LAYER 0

Renderer* g_Renderer = nullptr;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
 
}

void Renderer::StartUp()
{
	CreateDeviceAndSwapChain();
	SetRenderTarget();
	SetViewport();
	
	m_VS = new VertexShader();
	m_PS = new PixelShader();

	m_VS->CompileShader(MAGNUS_VERTEX_SHADER, "vsmain", MAGNUS_VERTEX_SHADER_VER);
	m_VS->CreateShader();
	m_VS->LoadShader();
	
	m_PS->CompileShader(MAGNUS_PIXEL_SHADER, "psmain", MAGNUS_PIXEL_SHADER_VER);
	m_PS->CreateShader();
	m_PS->LoadShader();

	m_VB = new VertexBuffer();
	m_IB = new IndexBuffer();

	const float vertices[] =
	{
		-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //0
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, //1
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, //2
		 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f //3
	};

	const unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_VB->Load(vertices, 9, sizeof(vertices), m_VS->m_Blob->GetBufferPointer(), m_VS->m_Blob->GetBufferSize());
	m_VB->Bind();

	m_IB->Load(indices, _countof(indices));
	m_IB->Bind();
}

void Renderer::ShutDown()
{
	SAFE_RELEASE(m_SwapChain)
	SAFE_RELEASE(m_RenderTargetView)
	SAFE_RELEASE(m_Device)
	SAFE_RELEASE(m_Context)

	SAFE_DELETE_POINTER(m_VB)
	SAFE_DELETE_POINTER(m_IB)

	SAFE_DELETE_POINTER(m_VS)
	SAFE_DELETE_POINTER(m_PS)
}

// todo Create a header file for shader struct declarations and include that file in all the child shader files
// todo Add index buffers, get the mesh pipeline working for PCU
// todo Translate the D3d input layout in the the Predefined VertexLayout struct
// todo change the shaders to unions

void Renderer::CreateDeviceAndSwapChain()
{
	uint32_t deviceFlags = NULL;

#if DEBUG_LAYER
		deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BufferCount = 1;
	desc.BufferDesc.Width = static_cast<uint32_t>(MAGNUS_WINDOW_DIMS[1]);
	desc.BufferDesc.Height = static_cast<uint32_t>(MAGNUS_WINDOW_DIMS[3]);
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = static_cast<HWND>(g_Window->GetHandle());
	desc.SampleDesc.Count = 1;
	desc.Windowed = TRUE;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		deviceFlags,
		featureLevels, 
		_countof(featureLevels), 
		D3D11_SDK_VERSION,
		&desc,
		&m_SwapChain,
		&m_Device, 
		NULL, 
		&m_Context
	);

	LOG_CHECK(SUCCEEDED(result)) << "Couldn't create device and swapchain!!";
}

void Renderer::Present(UINT vsync)
{
	m_SwapChain->Present(vsync, 0);
}

void Renderer::SetRenderTarget()
{
	ID3D11Texture2D* backBuffer = nullptr;
	HRESULT result = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	LOG_CHECK(SUCCEEDED(result)) << "Couldn't get address of the back buffer!!";

	result = m_Device->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView);

	LOG_CHECK(SUCCEEDED(result)) << "Render Target View was not created!!";

	SAFE_RELEASE(backBuffer)

	m_Context->OMSetRenderTargets(1, &m_RenderTargetView, NULL);
}

void Renderer::SetViewport()
{
	 D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = MAGNUS_WINDOW_DIMS[0];
    viewport.TopLeftY = MAGNUS_WINDOW_DIMS[2];
    viewport.Width = MAGNUS_WINDOW_DIMS[1];
    viewport.Height = MAGNUS_WINDOW_DIMS[3];
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

    m_Context->RSSetViewports(1, &viewport);
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
	const float clearColor[] = {color.m_X, color.m_Y, color.m_Z, color.m_W};

	m_Context->ClearRenderTargetView(m_RenderTargetView, clearColor);
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

void Renderer::DrawRing(const Vec2& center, const float& radius, const Vec4& color)
{
	
}

void Renderer::DrawMesh()
{
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Context->DrawIndexed(6, 0, 0);
}

ID3D11Device* Renderer::GetDevice() const
{
	return m_Device;
}

ID3D11DeviceContext* Renderer::GetContext() const
{
	return m_Context;
}

#endif