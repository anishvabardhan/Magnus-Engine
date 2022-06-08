#include "TextureView.h"
#if DX11_API

#include "Renderer.h"

#include "Sampler.h"
#include "Shader.h"
#include "SwapChain.h"
#include "Engine/Window/Window.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Core/LogMessage.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/MeshBuilder.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Engine/Graphics/Font.h"
#include "Engine/Graphics/Camera.h"
#include "External/stb_image.h"

Renderer* g_Renderer = nullptr;

// todo understanding rendertargets
// todo next task: Setup a perspective view and Render a cube

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::StartUp()
{
	CreateDeviceAndSwapChain();
	CreateRenderTarget(Vec2(MAGNUS_WINDOW_DIMS[1], MAGNUS_WINDOW_DIMS[3]));
	SetRenderTargets();
	SetViewport();

	m_Shader = new Shader();

	m_Camera = new Camera();
	m_Camera->SetOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -2.0f, 2.0f);

	m_ModelCBO.Init(sizeof(ModelData));
	m_CameraCBO.Init(sizeof(ViewData));

	m_DefaultTexture = GetOrCreateTexture(MAGNUS_DEFAULT_TEXTURE);

	SetCamera();
}

void Renderer::ShutDown()
{
	SAFE_RELEASE(m_Device)
	SAFE_RELEASE(m_Context)

	SAFE_DELETE_POINTER(m_Shader)
	SAFE_DELETE_POINTER(m_Camera)
	SAFE_DELETE_POINTER(m_RenderTarget)
	SAFE_DELETE_POINTER(m_SwapChain)
	SAFE_DELETE_POINTER(m_DefaultTexture)
	SAFE_DELETE_POINTER(m_DefaultSampler)
}

void Renderer::SetCamera()
{
	ViewData cameraData;
	cameraData.m_Projection = m_Camera->GetProjection();
	cameraData.m_View = m_Camera->GetView();
	
	SetCameraBuffer(cameraData);
	BindBufferSlot(CBO_VIEW_SLOT, m_CameraCBO.GetBuffer());

	m_DefaultTexture->Bind(0);
	m_DefaultSampler->Bind(0);
}

void Renderer::CopyResource(Texture* source, Texture* dest)
{
	if(dest == nullptr)
	{//todo call handle through a getter.
		m_Context->CopyResource(m_SwapChain->GetBackBuffer()->m_Handle, source->m_Handle);
	}
	else
	{
		m_Context->CopyResource(dest->m_Handle, source->m_Handle);
	}
}

void Renderer::CreateDeviceAndSwapChain()
{
	uint32_t deviceFlags = NULL;

#if MAGNUS_DEBUG
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

	m_SwapChain = new SwapChain();

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		deviceFlags,
		featureLevels, 
		_countof(featureLevels), 
		D3D11_SDK_VERSION,
		&desc,
		&m_SwapChain->m_DeviceSwapChain,
		&m_Device, 
		NULL, 
		&m_Context
	);

	m_SwapChain->PostInitialise();

	LOG_CHECK(SUCCEEDED(result)) << "Couldn't create device and swapchain!!";

#if MAGNUS_DEBUG
	const char deviceDebugName[] = "Device";
    m_Device->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( deviceDebugName ),deviceDebugName );
	
	const char swapchainDebugName[] = "SwapChain";
    m_SwapChain->m_DeviceSwapChain->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( swapchainDebugName ),swapchainDebugName );
	
	const char contextDebugName[] = "Context";
    m_Context->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( contextDebugName ),contextDebugName );
#endif
}

void Renderer::Present(UINT vsync)
{
	CopyResource(m_RenderTarget);

	m_SwapChain->Present(vsync);
}

void Renderer::CreateRenderTarget(Vec2 texel)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width	                    = static_cast<int>(texel.m_X);
	desc.Height						= static_cast<int>(texel.m_Y);
	desc.MipLevels					= 1;
	desc.ArraySize					= 1;
	desc.Format						= DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count			= 1;																					
	desc.SampleDesc.Quality			= 0;																					
	desc.Usage						= D3D11_USAGE_DEFAULT;																	
	desc.BindFlags					= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags				= 0;																					
	desc.MiscFlags					= 0;

	m_RenderTarget = new Texture(desc);

	m_RenderTargetView = new TextureView(m_RenderTarget);

	m_RenderTargetView->CreateRenderTargetView();
}

void Renderer::SetRenderTargets()
{
	m_RenderTargetView->SetRenderTarget();
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

void Renderer::SetCameraBuffer(const ViewData& data)
{
	m_CameraCBO.CopyToGPU(&data);
}

void Renderer::SetModelBuffer(const ModelData& data)
{
	m_ModelCBO.CopyToGPU(&data);

}

void Renderer::BindBufferSlot(unsigned int slot, ID3D11Buffer* buffer)
{
	m_Context->VSSetConstantBuffers(slot, 1, &buffer);
	m_Context->PSSetConstantBuffers(slot, 1, &buffer);
}

void Renderer::CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next)
{
	
}

void Renderer::ClearScreen(const Vec4& color) const
{
	const float clearColor[] = {color.m_X, color.m_Y, color.m_Z, color.m_W};
	
	m_Context->ClearRenderTargetView(m_RenderTargetView->m_RTV, clearColor);
}

void Renderer::Drawtext(const Vec2& position, const Vec4& color, const String& asciiText, float quadHeight, Font* font, ModelData model)
{
	Font* f = CreateBitmapFont(MAGNUS_FONT_BITMAP);

	float quadWidth = quadHeight;

	AABB2 quadPos;
	AABB2 uvPos;

	quadPos.m_Mins.m_Y = 0.0f + position.m_Y;
	quadPos.m_Maxs.m_Y = quadHeight + position.m_Y;

	for (size_t i = 0; i < asciiText.size(); i++)
	{
		MeshBuilder mb = MeshBuilder();

		quadPos.m_Mins.m_X = (i * quadWidth) + position.m_X;
		quadPos.m_Maxs.m_X = ((i + 1) * quadWidth) + position.m_X;

		uvPos = f->GetGlyphUV(asciiText[i]);
		
		mb.m_Vertices.emplace_back(VertexMaster(Vec3(quadPos.m_Mins.m_X, quadPos.m_Mins.m_Y, 0.0f), color, Vec2(uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y))); //0
	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Mins.m_Y, 0.0f), color, Vec2(uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y))); //1
	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Maxs.m_Y, 0.0f), color, Vec2(uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y))); //2
	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(quadPos.m_Mins.m_X, quadPos.m_Maxs.m_Y, 0.0f), color, Vec2(uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y))); //3

	    Mesh* mesh = mb.CreateMesh<VertexPCU>(6);
		
	    SetModelBuffer(model);
		BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	    DrawMesh(mesh);
	    
	    SAFE_DELETE_POINTER(mesh)
		SAFE_DELETE_POINTER(f)
	}
}

void Renderer::DrawAABB2(const AABB2& aabb2, const Vec4& color, ModelData model)
{
	MeshBuilder mb = MeshBuilder();

	mb.m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Mins.m_X, aabb2.m_Mins.m_Y, 0.0f), color, Vec2(0.0f, 0.0f))); //0
	mb.m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Mins.m_X, aabb2.m_Maxs.m_Y, 0.0f), color, Vec2(0.0f, 1.0f))); //1
	mb.m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Maxs.m_X, aabb2.m_Maxs.m_Y, 0.0f), color, Vec2(1.0f, 1.0f))); //2
	mb.m_Vertices.emplace_back(VertexMaster(Vec3(aabb2.m_Maxs.m_X, aabb2.m_Mins.m_Y, 0.0f), color, Vec2(1.0f, 0.0f))); //3

	Mesh* mesh = mb.CreateMesh<VertexPCU>(6);
	
	SetModelBuffer(model);
	BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	DrawMesh(mesh);

	SAFE_DELETE_POINTER(mesh)
}

void Renderer::DrawHollowAABB2(const AABB2& aabb2, const float& thickness, const Vec4& color, ModelData model)
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

void Renderer::DrawLine(Vec2& start, Vec2& end, const float& thickness, const Vec4& color, ModelData model)
{
	Vec2 distance = end - start;
	Vec2 forward = distance.GetNormalised();

	forward.SetLength(thickness / 2.0f);
	Vec2 left = forward.GetRotated90Degrees();

	Vec2 endLeft = end + forward + left;
	Vec2 endRight = end + forward - left;
	Vec2 startLeft = start - forward + left;
	Vec2 startRight = start - forward - left;

	MeshBuilder mb = MeshBuilder();

	mb.m_Vertices.emplace_back(VertexMaster(Vec3(startLeft.m_X,  startLeft.m_Y,  0.0f), color, Vec2(0.0f, 0.0f)));   //0
	mb.m_Vertices.emplace_back(VertexMaster(Vec3(endLeft.m_X,    endLeft.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //1
	mb.m_Vertices.emplace_back(VertexMaster(Vec3(endRight.m_X,   endRight.m_Y,   0.0f), color, Vec2(1.0f, 1.0f)));   //2
	mb.m_Vertices.emplace_back(VertexMaster(Vec3(startRight.m_X, startRight.m_Y, 0.0f), color, Vec2(0.0f, 1.0f)));   //3

	Mesh* mesh = mb.CreateMesh<VertexPCU>(6);
	
    SetModelBuffer(model);
	BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	DrawMesh(mesh);

	SAFE_DELETE_POINTER(mesh)
}

void Renderer::DrawArrow(Vec2& start, Vec2& end, const float& thickness, const Vec4& color, ModelData model)
{
	Vec2 distance = end - start;
	Vec2 forward = distance.GetNormalised();

	forward.SetLength(thickness / 2.0f);
	Vec2 left = forward.GetRotated90Degrees();

	Vec2 endLeft = end - forward + left;
	Vec2 endRight = end - forward - left;
	Vec2 startLeft = start - forward + left;
	Vec2 startRight = start - forward - left;

	MeshBuilder mb1 = MeshBuilder();

	mb1.m_Vertices.emplace_back(VertexMaster(Vec3(startLeft.m_X,  startLeft.m_Y,  0.0f), color, Vec2(0.0f, 0.0f)));   //0
	mb1.m_Vertices.emplace_back(VertexMaster(Vec3(endLeft.m_X,    endLeft.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //1
	mb1.m_Vertices.emplace_back(VertexMaster(Vec3(endRight.m_X,   endRight.m_Y,   0.0f), color, Vec2(1.0f, 1.0f)));   //2
	mb1.m_Vertices.emplace_back(VertexMaster(Vec3(startRight.m_X, startRight.m_Y, 0.0f), color, Vec2(0.0f, 1.0f)));   //3

	Mesh* mesh1 = mb1.CreateMesh<VertexPCU>(6);
	
	SetModelBuffer(model);
	BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	DrawMesh(mesh1);

	SAFE_DELETE_POINTER(mesh1)

	float Orientation = ( end - start ).GetAngleDegrees();
	Vec2 rightVert = Vec2::MakeFromPolarDegrees( Orientation - 25.f , 3 * thickness );
	Vec2 leftVert = Vec2::MakeFromPolarDegrees( Orientation + 25.f , 3 * thickness );

	Vec2 top = end - forward;
	Vec2 bottomLeft = end - leftVert;
	Vec2 bottomRight = end - rightVert;

	MeshBuilder mb2 = MeshBuilder();

	mb2.m_Vertices.emplace_back(VertexMaster(Vec3(top.m_X,           top.m_Y,           0.0f), color, Vec2(0.0f, 0.0f)));   //0
	mb2.m_Vertices.emplace_back(VertexMaster(Vec3(bottomLeft.m_X,    bottomLeft.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //1
	mb2.m_Vertices.emplace_back(VertexMaster(Vec3(bottomRight.m_X,   bottomRight.m_Y,   0.0f), color, Vec2(0.5f, 1.0f)));   //2

	Mesh* mesh2 = mb2.CreateMesh<VertexPCU>(3);

	SetModelBuffer(model);
	BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	DrawMesh(mesh2);

	SAFE_DELETE_POINTER(mesh2)
}

void Renderer::DrawDisc(const Vec2& center, const float& radius, const Vec4& color, ModelData model)
{
	for(int i = 0; i < NUM_OF_DISC_VERTICES; i++)
	{
		MeshBuilder mb = MeshBuilder();

		mb.m_Vertices.emplace_back(VertexMaster(Vec3(center.m_X,  center.m_Y,0.0f), color, Vec2(0.0f, 0.0f)));   //0

		float startDeg, endDeg;
		float angle = 360.0f / NUM_OF_DISC_VERTICES;
		Vec2 start, end;

		startDeg = angle * static_cast<float>(i);
		endDeg = angle * static_cast<float>(i + 1);

		start = Vec2(center.m_X + cosf(toRadians(startDeg)) * radius, center.m_Y + sinf(toRadians(startDeg)) * radius);
		end = Vec2(center.m_X + cosf(toRadians(endDeg)) * radius, center.m_Y + sinf(toRadians(endDeg)) * radius);

	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(end.m_X,   end.m_Y, 0.0f), color, Vec2(1.0f, 0.0f)));   //1
	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(start.m_X,     start.m_Y,   0.0f), color, Vec2(0.5f, 1.0f)));   //2
	    
	    Mesh* mesh = mb.CreateMesh<VertexPCU>(3);
	    
	    SetModelBuffer(model);
		BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	    DrawMesh(mesh);

		SAFE_DELETE_POINTER(mesh)
	}
}

void Renderer::DrawRing(const Vec2& center, const float& radius, const Vec4& color, ModelData model)
{
	for(int i = 0; i < NUM_OF_DISC_VERTICES; i++)
	{
		float startDeg, endDeg;
		float angle = 360.0f / NUM_OF_DISC_VERTICES;
		Vec2 start, end;

		startDeg = angle * static_cast<float>(i);
		endDeg = angle * static_cast<float>(i + 1);

		start = Vec2(center.m_X + cosf(toRadians(startDeg)) * radius, center.m_Y + sinf(toRadians(startDeg)) * radius);
		end = Vec2(center.m_X + cosf(toRadians(endDeg)) * radius, center.m_Y + sinf(toRadians(endDeg)) * radius);

		MeshBuilder mb = MeshBuilder();

		mb.m_Vertices.emplace_back(VertexMaster(Vec3(end.m_X,    end.m_Y,    0.0f), color, Vec2(1.0f, 0.0f)));   //0
	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(start.m_X,  start.m_Y,  0.0f), color, Vec2(0.0f, 0.0f)));   //1
	    mb.m_Vertices.emplace_back(VertexMaster(Vec3(start.m_X - (RING_THICKNESS * cosf(toRadians(startDeg))), start.m_Y - (RING_THICKNESS * sinf(toRadians(startDeg))), 0.0f), color, Vec2(0.0f, 1.0f)));   //2
		mb.m_Vertices.emplace_back(VertexMaster(Vec3(end.m_X - (RING_THICKNESS * cosf(toRadians(endDeg))), end.m_Y - (RING_THICKNESS * sinf(toRadians(endDeg))),   0.0f), color, Vec2(1.0f, 1.0f)));         //3

	    Mesh* mesh = mb.CreateMesh<VertexPCU>(6);

	    SetModelBuffer(model);
		BindBufferSlot(CBO_MODEL_SLOT, m_ModelCBO.GetBuffer());

	    DrawMesh(mesh);

		SAFE_DELETE_POINTER(mesh)
	}
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

Font* Renderer::CreateBitmapFont(const String& fontPath)
{
	Texture* texture = new Texture(fontPath);
	LOG_CHECK(texture != nullptr) << "Data is null";

	SpriteSheet* bitMapsheet = new SpriteSheet(*texture, 16, 16);
	LOG_CHECK(bitMapsheet != nullptr) << "Data is null";

	Font* newFont = new Font(*bitMapsheet);
	LOG_CHECK(newFont != nullptr) << "Data is null";

	return newFont;
}

Texture* Renderer::GetOrCreateTexture(const String& texturePath)
{
	m_DefaultSampler = new Sampler(SAMPLER_BILINEAR);
	m_DefaultSampler->Initialise();

	if(m_LoadedTextures.find(texturePath) != m_LoadedTextures.end())
		return m_LoadedTextures[texturePath];

	Texture* texture = new Texture(texturePath);

	m_LoadedTextures[texturePath] = texture;

	//todo below code should be a part of texture constructor or a texture function

	stbi_set_flip_vertically_on_load(1);
	m_LoadedTextures[texturePath]->m_ImageData = stbi_load(m_LoadedTextures[texturePath]->m_FilePath.c_str(), 
		&m_LoadedTextures[texturePath]->m_Width, 
		&m_LoadedTextures[texturePath]->m_Height, 
		&m_LoadedTextures[texturePath]->m_Channels, 4);

	m_LoadedTextures[texturePath]->Initialise();

	return m_LoadedTextures[texturePath];
}

#endif