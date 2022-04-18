#pragma once

#include "Engine/Core/CoreIncludes.h"

#if DX11_API

#include <d3d11.h>

class VertexBuffer
{
	ID3D11Buffer* m_Buffer = nullptr;
	uint32_t m_VertexSize;
public:
	VertexBuffer();
	~VertexBuffer();

	void Load(const void* data, uint32_t vertexSize, uint32_t arraySize);
	void Bind();
	void Release();
};

#endif