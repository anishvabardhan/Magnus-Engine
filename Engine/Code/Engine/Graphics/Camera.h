#pragma once

#include "Engine/Maths/Mat4.h"
#include "DIRECTX11/Buffers/ConstantBuffer.h"

class Camera
{
	Mat4 m_Projection;
	Mat4 m_View;
	Mat4 m_CamMatrix;

	Vec3 m_Position;
	Vec3 m_Rotation;

	ConstantBuffer m_CameraCBO;
public:
	Camera();
	~Camera();

	void SetOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
	void SetPersp(float fov, float aspectRatio, float nearZ, float farZ);

	void Setup();

	Mat4 GetProjection() const;
	Mat4 GetView() const;

	void SetPosition(Vec3 pos);
	void SetRotation(Vec3 rotation);
};
