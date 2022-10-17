  #include "MeshBuilder.h"

#include "Mesh.h"

MeshBuilder::MeshBuilder()
{
	
}

MeshBuilder::~MeshBuilder()
{
}

template <typename FORMAT>
Mesh* MeshBuilder::CreateMesh(unsigned int numOfVertices)
{
	Mesh* mesh = new Mesh();

	size_t size = m_Vertices.size();
	FORMAT* temp = new FORMAT[sizeof(FORMAT) * size]; 

	for(size_t index = 0; index < size; index++)
	{
		temp[index] = FORMAT(m_Vertices[index]);
	}

	mesh->CopyToGPU(temp, (uint32_t)size * sizeof(FORMAT), numOfVertices, &FORMAT::m_Layout);

	delete[] temp;
	temp = nullptr;

	return mesh;
}

