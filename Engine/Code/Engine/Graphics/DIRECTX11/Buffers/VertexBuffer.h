#pragma once

#if DX11_API

class VertexBuffer
{
	unsigned int m_RendererID;
public:
	explicit VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};

#endif