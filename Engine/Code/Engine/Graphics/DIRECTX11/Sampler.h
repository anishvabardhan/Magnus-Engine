#pragma once

#if DX11_API

#include <d3d11.h>

enum SAMPLER_TYPE
{
	SAMPLER_POINT,
	SAMPLER_BILINEAR,
	SAMPLER_TRILINEAR
};

class Sampler
{
	ID3D11SamplerState* m_Handle = nullptr;
	SAMPLER_TYPE m_SamplerType;
public:
	Sampler(SAMPLER_TYPE samplerType);
	~Sampler();

	void Initialise();
	void Bind(unsigned int slot);
};

#endif