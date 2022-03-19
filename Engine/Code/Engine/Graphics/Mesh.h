#pragma once

class VertexBuffer;
class IndexBuffer;

struct Mesh
{
	int m_Indices = 6;
	VertexBuffer* m_VBO = nullptr;
	const void* m_Data = nullptr;
	IndexBuffer* m_IBO = nullptr;

	Mesh(const void* data, void* shaderByteCode, size_t shaderByteSize);
	~Mesh();

	void CopyToGPU(void* shaderByteCode, size_t shaderByteSize);
};