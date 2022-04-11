#pragma once
#include "Shader.h"

#if DX11_API

#include <d3d11.h>

#include "Engine/Core/CoreIncludes.h"

#define SAFE_RELEASE(ptr) if(ptr != nullptr) {ptr->Release(); ptr = nullptr;}

class Texture;
class Font;
class FrameBuffer;
class VertexShader;
class PixelShader;
class VertexBuffer;
class IndexBuffer;
struct MeshBuilder;
struct Mesh;
class Shader;

class Renderer
{
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_Context = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11InputLayout* m_Layout = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;

	VertexShader* m_VS = nullptr;
	PixelShader* m_PS = nullptr;

	Shader* m_Shader = nullptr;

	VertexBuffer* m_VB = nullptr;
	IndexBuffer* m_IB = nullptr;
public:
	Renderer();
	~Renderer();

	void StartUp();
	void ShutDown();

	void CreateDeviceAndSwapChain();
	void Present(UINT vsync);
	void SetRenderTarget();
	void SetViewport();

	void SwappingBuffers();

	void BindDefaultShader();
	void BindFont(const Font* font, int textureSlot);
	void BindTexture(const Texture* texture = nullptr, int textureSlot = 0);

	// MVP UNIFORMS UPDATION METHODS
	void SetCameraUniform(const Mat4& camera);
	void SetModelTranslation(const Mat4& transform = Mat4::Identity());

	void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);

	void ClearColor(const Vec4& color = Color::CLEAR_COLOR) const;
	
	// DRAW CALL METHODS
	void Drawtext(const Vec2& position, const Vec4& color, const String& asciiText, float quadHeight, Font* font);
	void DrawAABB2(const AABB2& aabb2, const Vec4& color);
	void DrawHollowAABB2(const AABB2& aabb2, const float& thickness, const Vec4& color);
	void DrawLine(Vec2& start, Vec2& end, const float& thickness, const Vec4& color);
	void DrawArrow(Vec2& start, Vec2& end, const float& thickness, const Vec4& color);
	void DrawDisc(const Vec2& center, const float& radius, const Vec4& color);
	void DrawRing(const Vec2& center, const float& radius, const Vec4& color);

	void DrawMesh(Mesh* mesh);

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;

	void* GetShaderByteCode() { return m_VS->m_Blob->GetBufferPointer(); }
	size_t GetShaderByteSize() { return m_VS->m_Blob->GetBufferSize(); }
};

extern Renderer* g_Renderer;

#endif