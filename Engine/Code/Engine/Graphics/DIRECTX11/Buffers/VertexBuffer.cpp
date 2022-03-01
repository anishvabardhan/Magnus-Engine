#if DX11_API
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_RendererID(0)
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind() const
{
}

void VertexBuffer::UnBind() const
{
}
#endif