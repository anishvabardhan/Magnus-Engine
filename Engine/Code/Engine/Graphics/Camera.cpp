#include "Camera.h"

#include "Renderer.h"

Camera::Camera()
	: m_Projection(Mat4::Identity()), m_View(Mat4::Identity()), m_CamMatrix(Mat4::Identity())
{
	m_CameraCBO.Init(sizeof(ViewData));

	m_Position = Vec3(0.0f, 0.0f, -25.0f);
}

Camera::~Camera()
{
}

Mat4 Camera::SetOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
	m_Projection = Mat4::Orthographic(left, right, bottom, top, nearZ, farZ);

	return m_Projection;
}

Mat4 Camera::SetPersp(float fov, float aspectRatio, float nearZ, float farZ)
{
	m_Projection = Mat4::Perspective(fov, aspectRatio, nearZ, farZ);

	return m_Projection;
}

void Camera::Update(float deltaseconds)
{
	m_CamMatrix = Mat4::Translation(m_Position) * Mat4::Rotation3D(m_Rotation.m_X, m_Rotation.m_Y, m_Rotation.m_Z);

	m_View = Mat4::InvertFast(m_CamMatrix);

	Setup();
}

void Camera::Setup()
{
	ViewData cameraData;
	cameraData.m_Projection = m_Projection;
	cameraData.m_View = m_View;

	m_CameraCBO.CopyToGPU(&cameraData);

	g_Renderer->BindBufferSlot(CBO_VIEW_SLOT, m_CameraCBO.GetBuffer());
}

Mat4 Camera::GetProjection() const
{
	return m_Projection;
}

Mat4 Camera::GetView() const
{
	return m_View;
}

void Camera::SetPosition(Vec3 pos)
{
	m_Position = pos;
}

void Camera::SetRotation(Vec3 rotation)
{
	m_Rotation = rotation;
}
