#include "Vertex.h"

std::vector<VertexBufferElement> VertexPCU::m_Attributes = {
	VertexBufferElement("POSITION", MAGNUS_FORMAT_3_FLOAT, offsetof(VertexPCU, m_Pos)),
	VertexBufferElement("COLOR", MAGNUS_FORMAT_4_FLOAT, offsetof(VertexPCU, m_Color))
};

VertexBufferLayout VertexPCU::m_Layout(VertexPCU::m_Attributes);

VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement> element)
	: m_Element(element)
{
}

VertexBufferElement::VertexBufferElement(std::string semanticName, MAGNUS_FORMAT format, unsigned int alignedOffset)
	: m_SemanticName(semanticName), m_Format(format), m_AlignedOffset(alignedOffset)
{
}

VertexPCU::VertexPCU(const VertexMaster& master)
	: m_Pos(master.m_Pos), m_Color(master.m_Color), m_UV(master.m_UV)
{
}

VertexPCU::VertexPCU(const Vec3& position, const Vec4& color, const Vec2& uv)
	: m_Pos(position), m_Color(color), m_UV(uv)
{
}

VertexPCU::~VertexPCU()
{
}

VertexMaster::VertexMaster(const VertexPCU& pcu)
	:m_Pos(pcu.m_Pos), m_Color(pcu.m_Color), m_UV(pcu.m_UV)
{
}

VertexMaster::VertexMaster(const Vec3& position, const Vec4& color, const Vec2& uv)
    : m_Pos(position), m_Color(color), m_UV(uv)
{
}
