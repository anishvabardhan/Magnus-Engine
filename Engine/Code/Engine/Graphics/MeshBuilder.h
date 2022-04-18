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
	void CreateMesh(uint32_t indices);
};

template void MeshBuilder::CreateMesh<VertexPCU>(uint32_t indices);

extern MeshBuilder* g_MB;