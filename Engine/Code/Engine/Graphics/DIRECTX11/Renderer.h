#pragma once

#if DX11_API

#include "Engine/Core/CoreIncludes.h"

class Texture;
class Font;
class FrameBuffer;
struct Mesh;

extern void* m_OurWindowHandleToDeviceContext;
extern void* m_OurWindowHandleToRenderContext;

// TODO First thing: Link DX libs/dll through premake, then create device and swap chain. Read on RenderTargets.

class Renderer
{
public:
	Renderer();
	~Renderer();

	void StartUp();
	void ShutDown();

	void SwappingBuffers();

	bool MakeContextCurrent(void* hdc, void* hglrc);
	void CreateOldRenderContext(void* hdc);
	void CreateRealRenderContext(void* hdc, int major, int minor);

	void BindDefaultShader();
	void BindFont(const Font* font, int textureSlot);
	void BindTexture(const Texture* texture = nullptr, int textureSlot = 0);

	// MVP UNIFORMS UPDATION METHODS
	void SetCameraUniform(const Mat4& camera);
	void SetModelTranslation(const Mat4& transform = Mat4::Identity());

	void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);
	void Clear() const;
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
};

extern Renderer* g_Renderer;
#endif