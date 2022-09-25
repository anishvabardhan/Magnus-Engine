#pragma once
#include "Shader.h"

#if DX11_API

#include <d3d11.h>

#include "Engine/Core/CoreIncludes.h"
#include "Buffers/ConstantBuffer.h"
#include "RendererStruct.h"

#define SAFE_RELEASE(ptr) if(ptr != nullptr) {ptr->Release(); ptr = nullptr;}

class Texture;
class TextureView;
class Sampler;
class Font;
class FrameBuffer;
class VertexShader;
class PixelShader;
struct MeshBuilder;
struct Mesh;
class Shader;
class ConstantBuffer;
class Camera;
class SwapChain;

class Renderer
{
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_Context = nullptr;

	SwapChain* m_SwapChain = nullptr;
	TextureView* m_RenderTargetView = nullptr;

	ConstantBuffer m_ModelCBO;
	ConstantBuffer m_CameraCBO;

	Shader* m_Shader = nullptr;
	Camera* m_Camera = nullptr;

	Texture* m_RenderTarget = nullptr;
	Texture* m_DefaultTexture = nullptr;
	Sampler* m_DefaultSampler = nullptr;

	std::map<String, Texture*> m_LoadedTextures;
public:
	Renderer();
	~Renderer();

	void StartUp();
	void ShutDown();

	void CreateDeviceAndSwapChain();
	void Present(bool vsync);
	void CreateRenderTarget(Vec2 texel);
	void SetRenderTarget(TextureView* renderTarget);
	void SetViewport();
	void SetCamera();
	void SwappingBuffers();
	void CopyResource(Texture* source, Texture* dest = nullptr);

	void BindDefaultShader();
	void BindFont(const Font* font, int textureSlot);
	void BindTexture(const Texture* texture = nullptr, int textureSlot = 0);

	// MVP UNIFORMS UPDATION METHODS
	void SetCameraBuffer(const ViewData& data);
	void SetModelBuffer(const ModelData& data);
	void BindBufferSlot(unsigned int slot, ID3D11Buffer* buffer);

	void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);

	void ClearScreen(const Vec4& color = Color::CLEAR_COLOR) const;
	
	// DRAW CALL METHODS
	void Drawtext(const Vec2& position, const Vec4& color, const String& asciiText, float quadHeight, Font* font = nullptr, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawAABB2(const AABB2& aabb2, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawHollowAABB2(const AABB2& aabb2, const float& thickness, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawCube(const Vec3& center, const Vec3& dimensions, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawLine(Vec2& start, Vec2& end, const float& thickness, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawArrow(Vec2& start, Vec2& end, const float& thickness, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawDisc(const Vec2& center, const float& radius, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});
	void DrawRing(const Vec2& center, const float& radius, const Vec4& color, ModelData model = {Mat4::Translation(Vec3::ZERO)});

	void DrawMesh(Mesh* mesh);

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;

	void* GetShaderByteCode() { return m_Shader->m_VSBlob->GetBufferPointer(); }
	size_t GetShaderByteSize() { return m_Shader->m_VSBlob->GetBufferSize(); }
private:
	Texture* GetOrCreateTexture(const String& texturePath);
	Font* CreateBitmapFont(const String& fontPath);
};

extern Renderer* g_Renderer;

#endif