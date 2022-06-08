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

	VertexBuffer* m_VBO = nullptr;
	IndexBuffer* m_IBO = nullptr;

	uint32_t m_Indices = 6;

	Mesh();
	~Mesh();

	void CopyToGPU(const void* data, uint32_t arraySize, VertexBufferLayout* layout);
};