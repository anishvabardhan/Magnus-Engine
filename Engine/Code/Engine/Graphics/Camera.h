#pragma once

#include "Engine/Maths/Mat4.h"

class Camera
{
	Mat4 m_Projection;
	Mat4 m_View;
public:
	Camera();
	~Camera();

	Mat4 SetOrtho(float left, float right, float bottom, float top, float near, float far);
	Mat4 SetPersp(float fov, float aspectRatio, float near, float far);

	Mat4 GetProjection() const;
	Mat4 GetView() const;
};
