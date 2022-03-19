#include "Mesh.h"

#if OPENGL_API
#include "OPENGL/Buffers/VertexArrayObject.h"
#include "OPENGL/Buffers/IndexBuffer.h"
#elif DX11_API
#include "DIRECTX11/Buffers/VertexBuffer.h"
#include "DIRECTX11/Buffers/IndexBuffer.h"
#endif

#include "MeshBuilder.h"
#include "Vertex.h"

Mesh::Mesh(const void* data, void* shaderByteCode, size_t shaderByteSize)
	: m_Data(data)
{
	CopyToGPU(shaderByteCode, shaderByteSize);
}

Mesh::~Mesh()
{
	SAFE_DELETE_POINTER(m_VBO)
	SAFE_DELETE_POINTER(m_IBO)
	SAFE_DELETE_POINTER(m_Data)
}

void Mesh::CopyToGPU(void* shaderByteCode, size_t shaderByteSize)
{
	m_VBO = new VertexBuffer();
	m_VBO->Load(m_Data, 9, sizeof(m_Data), shaderByteCode, shaderByteSize);
	m_VBO->Bind();

	if(m_Indices == 6)
	{
		const unsigned int indices[] =
	    {
	    	0, 1, 2,
	    	2, 3, 0
	    };

	    m_IBO = new IndexBuffer();

		m_IBO->Load(indices, _countof(indices));
		m_IBO->Bind();
	}

}