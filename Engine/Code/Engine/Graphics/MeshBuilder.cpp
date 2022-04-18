#include "MeshBuilder.h"

#include "Mesh.h"

MeshBuilder* g_MB = nullptr;

MeshBuilder::MeshBuilder()
{
}

MeshBuilder::~MeshBuilder()
{
}

template <typename FORMAT>
Mesh* MeshBuilder::CreateMesh(uint32_t indices)
{
	Mesh* mesh = new Mesh();

	size_t size = m_Vertices.size();
	FORMAT* temp = new FORMAT[sizeof(FORMAT) * size]; 

	for(size_t index = 0; index < size; index++)
	{
		temp[index] = FORMAT(m_Vertices[index]);
	}

	mesh->m_Indices = indices;
	mesh->CopyToGPU(temp, (uint32_t)size * sizeof(FORMAT), &FORMAT::m_Layout);

	while(!m_Vertices.empty())
	{
		m_Vertices.pop_back();
	}

	return mesh;
}