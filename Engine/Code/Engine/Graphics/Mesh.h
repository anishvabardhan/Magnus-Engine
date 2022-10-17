#pragma once

#include <d3d11.h>

#include "Engine/Core/CoreIncludes.h"

class VertexBuffer;
class IndexBuffer;
struct VertexBufferLayout;

struct Mesh
{
	ID3D11InputLayout* m_Layout = nullptr;
	D3D11_INPUT_ELEMENT_DESC m_Attribs[3];
	unsigned int m_NumOfVertices;

	VertexBuffer* m_VBO = nullptr;
	IndexBuffer* m_IBO = nullptr;

	Mesh();
	~Mesh();

	void CopyToGPU(const void* data, uint32_t arraySize, unsigned int numOfVertices, VertexBufferLayout* layout);
	void SetIndices(const unsigned int* indices, const unsigned int numOfIndices);
};