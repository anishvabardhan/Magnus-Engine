#include "MeshBuilder.h"

#include "Mesh.h"

MeshBuilder* g_MB = nullptr;

MeshBuilder::MeshBuilder()
{
	m_Mesh = new Mesh();
}

MeshBuilder::~MeshBuilder()
{
	SAFE_DELETE_POINTER(m_Mesh)
}

template <typename FORMAT>
void MeshBuilder::CreateMesh(uint32_t indices)
{
	delete m_Mesh;
	m_Mesh = new Mesh();

	size_t size = m_Vertices.size();
	FORMAT* temp = new FORMAT[sizeof(FORMAT) * size]; 

	for(size_t index = 0; index < size; index++)
	{
		temp[index] = FORMAT(m_Vertices[index]);
	}

	m_Mesh->m_Indices = indices;
	m_Mesh->CopyToGPU(temp, (uint32_t)size * sizeof(FORMAT), &FORMAT::m_Layout);

	while(!m_Vertices.empty())
	{
		m_Vertices.pop_back();
	}
}