#pragma once

#include "Engine/Core/CoreIncludes.h"
#include "Vertex.h"

struct Mesh;

struct MeshBuilder
{
	Vec4 m_Color;
	VertexMaster m_VertMast;
	std::vector<VertexMaster> m_Vertices;

	MeshBuilder();
	~MeshBuilder();

	void Color3f(Vec4 color);
	void TexCoord2f(Vec2 uv);
	void Position3f(Vec3 position);
	void Vert(const VertexMaster& master);

	template<typename FORMAT>
	Mesh* CreateMesh(void* shaderByteCode, size_t shaderByteSize);
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>(void* shaderByteCode, size_t shaderByteSize);