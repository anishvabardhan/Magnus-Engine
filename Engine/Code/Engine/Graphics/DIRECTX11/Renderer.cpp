#if DX11_API

#include "Renderer.h"

Renderer* g_Renderer = nullptr;

void* m_OurWindowHandleToDeviceContext = nullptr;
void* m_OurWindowHandleToRenderContext = nullptr;

Renderer::Renderer()
{
 
}

Renderer::~Renderer()
{
 
}

void Renderer::StartUp()
{
 
}

void Renderer::ShutDown()
{
	
}

void Renderer::SwappingBuffers()
{
	
}

bool  Renderer::MakeContextCurrent(void* hdc, void* hglrc)
{
	return false;
}

void Renderer::CreateOldRenderContext(void* hdc)
{
}

void Renderer::CreateRealRenderContext(void* hdc, int major, int minor)
{
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

void Renderer::Clear() const
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