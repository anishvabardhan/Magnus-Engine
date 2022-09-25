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
	Mesh* CreateMesh(const unsigned int* indices = nullptr);
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>(const unsigned int* indices);