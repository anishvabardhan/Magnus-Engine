#if OPENGL_API
#include "VertexBuffer.h"

#include "Engine/Graphics/GLFunctions.h"
#include "..\..\DIRECTX11\Buffers\VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_RendererID(0)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
#endif