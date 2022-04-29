#pragma once

#include "Vertex.h"

#include <vector>

struct Mesh;

struct MeshBuilder
{
	std::vector<VertexMaster> m_Vertices;

	MeshBuilder();
	~MeshBuilder();

	template<typename FORMAT>
	Mesh* CreateMesh(uint32_t indices);
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>(uint32_t indices);
