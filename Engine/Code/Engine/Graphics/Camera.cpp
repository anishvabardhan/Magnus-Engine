#include "Camera.h"

Camera::Camera()
	: m_Projection(Mat4::Identity()), m_View(Mat4::Identity())
{
}

Camera::~Camera()
{
}

Mat4 Camera::SetOrtho(float left, float right, float bottom, float top, float near, float far)
{
	m_Projection = Mat4::Orthographic(left, right, bottom, top, near, far);

	return m_Projection;
}

Mat4 Camera::SetPersp(float fov, float aspectRatio, float near, float far)
{
	m_Projection = Mat4::Perspective(fov, aspectRatio, near, far);

	return m_Projection;
}

Mat4 Camera::GetProjection() const
{
	return m_Projection;
}

Mat4 Camera::GetView() const
{
	return m_View;
}
