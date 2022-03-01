#include "Mesh.h"

#include "OPENGL/Buffers/IndexBuffer.h"
#include "MeshBuilder.h"
#include "Vertex.h"

Mesh::Mesh(const void* data, VertexBufferLayout* layout)
	: m_Layout(layout), m_Data(data)
{
	CopyToGPU();
}

Mesh::~Mesh()
{
}

void Mesh::CopyToGPU()
{
	
}

void Mesh::Begin(DRAW_TYPE drawType)
{
	m_DrawType = drawType;
	
}

void Mesh::End()
{
}