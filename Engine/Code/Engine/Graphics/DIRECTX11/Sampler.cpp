#include "Engine/Core/LogMessage.h"

#if DX11_API

#include "Sampler.h"

#include "Renderer.h"

Sampler::Sampler(SAMPLER_TYPE samplerType)
	: m_SamplerType(samplerType)
{

}

Sampler::~Sampler()
{
	SAFE_RELEASE(m_Handle)
}

void Sampler::Initialise()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	if(m_SamplerType == SAMPLER_POINT)
	{
		desc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	}
	else if(m_SamplerType == SAMPLER_BILINEAR)
	{
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	}

	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT result = g_Renderer->GetDevice()->CreateSamplerState(&desc, &m_Handle);

	LOG_CHECK(SUCCEEDED(result)) << "Couldn't create SamplerState!!";
}

void Sampler::Bind(unsigned int slot)
{
	g_Renderer->GetContext()->PSSetSamplers(slot, 1, &m_Handle);
}

#endif
