#pragma once

#include "Engine/Core/CoreIncludes.h"
#if OPENGL_API
#include "Engine/Graphics/OPENGL/GLFunctions.h"
#elif DX11_API
#include <d3d11.h>
#endif
enum MAGNUS_FORMAT
{
	MAGNUS_FORMAT_3_FLOAT = DXGI_FORMAT_R32G32B32_FLOAT,
	MAGNUS_FORMAT_4_FLOAT = DXGI_FORMAT_R32G32B32A32_FLOAT
};

struct VertexPCU;

struct VertexBufferElement
{
	std::string m_SemanticName;
	MAGNUS_FORMAT m_Format;
	unsigned int m_AlignedOffset;

	VertexBufferElement(std::string semanticName, MAGNUS_FORMAT format, unsigned int alignedOffset);
};

struct VertexBufferLayout
{
	std::vector<VertexBufferElement> m_Element;
	unsigned int m_Stride;

	VertexBufferLayout(const std::vector<VertexBufferElement> element);
};

struct VertexMaster
{
	Vec3 m_Pos;
	Vec4 m_Color;
	Vec2 m_UV;

	VertexMaster() {}
	VertexMaster(const VertexPCU& pcu);
	VertexMaster(const Vec3& position, const Vec4& color, const Vec2& uv);
	~VertexMaster() {}
};

struct VertexPCU
{
	Vec3 m_Pos;
	Vec4 m_Color;
	Vec2 m_UV;

	VertexPCU() {}
	VertexPCU(const VertexMaster& master);
	VertexPCU(const Vec3& position, const Vec4& color, const Vec2& uv);
	~VertexPCU();

	static std::vector<VertexBufferElement> m_Attributes;
	static VertexBufferLayout m_Layout;
};