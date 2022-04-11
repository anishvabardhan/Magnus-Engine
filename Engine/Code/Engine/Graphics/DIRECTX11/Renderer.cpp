#if DX11_API

#include "Renderer.h"

#include "Engine/Window/Window.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Core/LogMessage.h"
#include "Shader.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/MeshBuilder.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"

#define DEBUG_LAYER 1

Renderer* g_Renderer = nullptr;

// todo look up debug names id3d resources
// todo swap chain flip discard
// todo finish implementation of all drawcalls
// todo get rid of all warnings
// todo read render targets

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

	//m_Shader = new Shader();

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

	g_MB = new MeshBuilder();

}

void Renderer::ShutDown()
{
	SAFE_RELEASE(m_SwapChain)
	SAFE_RELEASE(m_RenderTargetView)
	SAFE_RELEASE(m_Device)
	SAFE_RELEASE(m_Context)

	SAFE_DELETE_POINTER(m_VS)
	SAFE_DELETE_POINTER(m_PS)
}

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
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

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
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Mins.m_X, aabb2.m_Mins.m_Y, 0.0f), color, Vec2(0.0f, 0.0f))); //0
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Mins.m_X, aabb2.m_Maxs.m_Y, 0.0f), color, Vec2(1.0f, 0.0f))); //1
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Maxs.m_X, aabb2.m_Maxs.m_Y, 0.0f), color, Vec2(1.0f, 1.0f))); //2
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Maxs.m_X, aabb2.m_Mins.m_Y, 0.0f), color, Vec2(0.0f, 1.0f))); //3

	Mesh* mesh = g_MB->CreateMesh<VertexPCU>(6);

	DrawMesh(mesh);

	SAFE_DELETE_POINTER(mesh)
}

void Renderer::DrawHollowAABB2(const AABB2& aabb2, const float& thickness, const Vec4& color)
{
	Vec2 vertices[] = {
		Vec2(aabb2.m_Mins),
		Vec2(aabb2.m_Maxs.m_X, aabb2.m_Mins.m_Y),
	    Vec2(aabb2.m_Maxs),
	    Vec2(aabb2.m_Mins.m_X, aabb2.m_Maxs.m_Y)
	};

	DrawLine(vertices[0], vertices[1], thickness, color);
	DrawLine(vertices[1], vertices[2], thickness, color);
	DrawLine(vertices[2], vertices[3], thickness, color);
	DrawLine(vertices[3], vertices[0], thickness, color);
}

void Renderer::DrawLine(Vec2& start, Vec2& end, const float& thickness, const Vec4& color)
{
	Vec2 distance = end - start;
	Vec2 forward = distance.GetNormalised();

	forward.SetLength(thickness / 2.0f);
	Vec2 left = forward.GetRotated90Degrees();

	Vec2 endLeft = end + forward + left;
	Vec2 endRight = end + forward - left;
	Vec2 startLeft = start - forward + left;
	Vec2 startRight = start - forward - left;

	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(startLeft.m_X,  startLeft.m_Y,  0.0f), color, Vec2(0.0f, 0.0f)));   //0
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(endLeft.m_X,    endLeft.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //1
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(endRight.m_X,   endRight.m_Y,   0.0f), color, Vec2(1.0f, 1.0f)));   //2
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(startRight.m_X, startRight.m_Y, 0.0f), color, Vec2(0.0f, 1.0f)));   //3

	Mesh* mesh = g_MB->CreateMesh<VertexPCU>(6);

	DrawMesh(mesh);

	SAFE_DELETE_POINTER(mesh)
}

void Renderer::DrawArrow(Vec2& start, Vec2& end, const float& thickness, const Vec4& color)
{
	Vec2 distance = end - start;
	Vec2 forward = distance.GetNormalised();

	forward.SetLength(thickness / 2.0f);
	Vec2 left = forward.GetRotated90Degrees();

	Vec2 endLeft = end - forward + left;
	Vec2 endRight = end - forward - left;
	Vec2 startLeft = start - forward + left;
	Vec2 startRight = start - forward - left;

	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(startLeft.m_X,  startLeft.m_Y,  0.0f), color, Vec2(0.0f, 0.0f)));   //0
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(endLeft.m_X,    endLeft.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //1
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(endRight.m_X,   endRight.m_Y,   0.0f), color, Vec2(1.0f, 1.0f)));   //2
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(startRight.m_X, startRight.m_Y, 0.0f), color, Vec2(0.0f, 1.0f)));   //3

	Mesh* mesh1 = g_MB->CreateMesh<VertexPCU>(6);

	DrawMesh(mesh1);

	SAFE_DELETE_POINTER(mesh1)

	float Orientation = ( end - start ).GetAngleDegrees();
	Vec2 rightVert = Vec2::MakeFromPolarDegrees( Orientation - 25.f , 3 * thickness );
	Vec2 leftVert = Vec2::MakeFromPolarDegrees( Orientation + 25.f , 3 * thickness );

	Vec2 top = end - forward;
	Vec2 bottomLeft = end - leftVert;
	Vec2 bottomRight = end - rightVert;
	
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(top.m_X,           top.m_Y,           0.0f), color, Vec2(0.0f, 0.0f)));   //0
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(bottomLeft.m_X,    bottomLeft.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //1
	g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(bottomRight.m_X,   bottomRight.m_Y,   0.0f), color, Vec2(0.5f, 1.0f)));   //2

	Mesh* mesh2 = g_MB->CreateMesh<VertexPCU>(3);

	DrawMesh(mesh2);

	SAFE_DELETE_POINTER(mesh2)
}

void Renderer::DrawDisc(const Vec2& center, const float& radius, const Vec4& color)
{
	for(int i = 0; i < 1; i++)
	{
		g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(center.m_X,  center.m_Y,0.0f), color, Vec2(0.0f, 0.0f)));   //0

		float startDeg, endDeg;
		float angle = 360.0f / NUM_OF_DISC_VERTICES;
		Vec2 start, end;

		startDeg = angle * static_cast<float>(i);
		endDeg = angle * static_cast<float>(i + 1);

		start = Vec2(center.m_X + cosf(toRadians(startDeg)) * radius, center.m_Y + sinf(toRadians(startDeg)) * radius);
		end = Vec2(center.m_X + cosf(toRadians(endDeg)) * radius, center.m_Y + sinf(toRadians(endDeg)) * radius);

	    g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(start.m_X,   start.m_Y, 0.0f), color, Vec2(1.0f, 0.0f)));   //1
	    g_MB->m_Vertices.emplace_back(VertexMaster(Vec3(end.m_X,     end.m_Y,   0.0f), color, Vec2(0.5f, 1.0f)));   //2
	    
	    Mesh* mesh = g_MB->CreateMesh<VertexPCU>(3);
	    
	    DrawMesh(mesh);

		SAFE_DELETE_POINTER(mesh)
	}
}

void Renderer::DrawRing(const Vec2& center, const float& radius, const Vec4& color)
{
	
}

void Renderer::DrawMesh(Mesh* mesh)
{
	m_Context->IASetInputLayout(mesh->m_Layout);
	mesh->m_VBO->Bind();

	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if(mesh->m_Indices == 6)
	{
		mesh->m_IBO->Bind();

		m_Context->DrawIndexed(6, 0, 0);
	}
	else
	{
		m_Context->Draw(mesh->m_Indices, 0);
	}
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