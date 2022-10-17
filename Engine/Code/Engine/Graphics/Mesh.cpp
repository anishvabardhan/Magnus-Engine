#include "Mesh.h"

#if DX11_API

#include "Engine/Core/LogMessage.h"
#include "DIRECTX11/Buffers/VertexBuffer.h"
#include "DIRECTX11/Buffers/IndexBuffer.h"
#include "DIRECTX11/Renderer.h"
#include "Vertex.h"

Mesh::Mesh()
{
	m_VBO = new VertexBuffer();
	m_IBO = new IndexBuffer();
}

void Mesh::SetIndices(const unsigned int* indices, const unsigned int numOfIndices)
{
	m_IBO->Load(indices, numOfIndices);
}

Mesh::~Mesh()
{
	SAFE_DELETE_POINTER(m_VBO)
	SAFE_DELETE_POINTER(m_IBO)
	
	SAFE_RELEASE(m_Layout)
}

void Mesh::CopyToGPU(const void* data, uint32_t arraySize, unsigned int numOfVertices, VertexBufferLayout* layout)
{
	m_NumOfVertices = numOfVertices;
	m_VBO->Load(data, 9, arraySize);

	for(size_t i = 0; i < layout->m_Element.size(); i++)
	{
		m_Attribs[i] = {
			layout->m_Element[i].m_SemanticName.c_str(),
			0,
			(DXGI_FORMAT)layout->m_Element[i].m_Format,
			0,
			layout->m_Element[i].m_AlignedOffset,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};
	}

	HRESULT result = g_Renderer->GetDevice()->CreateInputLayout(m_Attribs, ARRAYSIZE(m_Attribs), g_Renderer->GetShaderByteCode(), g_Renderer->GetShaderByteSize(), &m_Layout);

	LOG_CHECK(SUCCEEDED(result)) << "Layout was not created!!";
#if MAGNUS_DEBUG
	const char layoutDebugName[] = "InputLayout";
    m_Layout->SetPrivateData( WKPDID_D3DDebugObjectName, _countof( layoutDebugName ),layoutDebugName );
#endif
}

#endif