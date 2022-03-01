#pragma once

#include "Engine/Graphics/OPENGL/GLFunctions.h"

struct VertexBufferLayout;
class VertexBuffer;
class IndexBuffer;

enum DRAW_TYPE{
	PRIMITIVE_TRIANGLES
};

struct Mesh
{
	int m_Indices = 6;
	VertexBuffer* m_VBO = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	const void* m_Data = nullptr;
	DRAW_TYPE m_DrawType;
	IndexBuffer* m_IBO = nullptr;

	Mesh(const void* data, VertexBufferLayout* layout);
	~Mesh();

	void CopyToGPU();
	void Begin(DRAW_TYPE drawType);
	void End();
};