#if DX11_API

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const Vec2 dimensions)
	: m_Dims(dimensions)
{
	Initialize();
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Bind()
{
}

void FrameBuffer::UnBind()
{
}

void FrameBuffer::Initialize()
{
	
}

unsigned int FrameBuffer::GetFrameBufferID() const
{
	return m_FrameBufferID;
}

unsigned int FrameBuffer::GetColorAttachmentID() const
{
	return m_ColorAttachment;
}
#endif