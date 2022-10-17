#pragma once

#include "Vertex.h"

#include <vector>

struct Mesh;

struct MeshBuilder
{
	Mesh* m_Mesh = nullptr;
	std::vector<VertexMaster> m_Vertices;

	MeshBuilder();
	~MeshBuilder();

	template<typename FORMAT>
	Mesh* CreateMesh(unsigned int numOfVertices = 0);
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>(unsigned int numOfVertices);