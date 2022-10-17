#pragma once

#include "Engine/Core/CoreIncludes.h"

#if DX11_API

#include <d3d11.h>

class IndexBuffer
{
	ID3D11Buffer* m_Buffer = nullptr;

	unsigned int m_Count;
public:
	IndexBuffer();
	~IndexBuffer();

	void Load(const void* data, unsigned int count);
	void Bind();
	void Release();

	inline unsigned int GetCount() const { return m_Count; }
};
#endif