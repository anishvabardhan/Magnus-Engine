#pragma once

#include "Engine/Maths/Mat4.h"

enum BufferSlot
{
	CBO_VIEW_SLOT = 0,
	CBO_MODEL_SLOT = 1
};

struct ModelData
{
	Mat4 m_Model;
};

struct ViewData
{
	Mat4 m_Projection;
	Mat4 m_View;
};