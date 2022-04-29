#pragma once

#if DX11_API

#include <d3d11.h>

class ConstantBuffer
{
	ID3D11Buffer* m_Buffer = nullptr;
	size_t m_DataByteSize;
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(size_t dataByteSize);
	void Map(const void* data);
	void Unmap();
	void Bind(unsigned int slot);
	void Release();
};

extern ConstantBuffer* g_CBO;

#endif