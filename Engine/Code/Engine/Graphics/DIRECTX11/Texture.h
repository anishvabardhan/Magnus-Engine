#pragma once
#include "Engine/Core/CoreIncludes.h"

#if DX11_API

#include <d3d11.h>

class Texture
{
	ID3D11ShaderResourceView* m_SRV = nullptr;
	ID3D11Texture2D* m_Handle = nullptr;

	D3D11_TEXTURE2D_DESC m_Desc = {};

	String m_FilePath;
	unsigned char* m_ImageData = nullptr;
	int m_Width;
	int m_Height;
	int m_Channels;
public:
	friend class TextureView;

	Texture(D3D11_TEXTURE2D_DESC desc);
	Texture(ID3D11Texture2D* handle);
	explicit Texture(String filePath);
	~Texture();

	void Initialise();
	void Bind(unsigned int slot);

	ID3D11Texture2D* GetHandle() const;
};

#endif