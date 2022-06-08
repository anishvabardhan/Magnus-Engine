#pragma once

#if DX11_API

#include <d3d11.h>

class ConstantBuffer
{
	size_t m_DataByteSize;
	ID3D11Buffer* m_Buffer = nullptr;
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(size_t dataByteSize);
	void CopyToGPU(const void* data);
	void Release();

	ID3D11Buffer* const GetBuffer();
};

#endif