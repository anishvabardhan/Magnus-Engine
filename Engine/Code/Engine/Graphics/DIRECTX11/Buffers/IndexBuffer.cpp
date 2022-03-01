#if DX11_API

#include "IndexBuffer.h"

// TODO exclude all gl based files, copy-paste renderer file and make one for DX11, similarly for buffers and shaders and textures

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
}

void IndexBuffer::UnBind() const
{
}
#endif