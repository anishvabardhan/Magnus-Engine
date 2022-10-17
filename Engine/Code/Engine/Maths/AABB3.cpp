#include "AABB3.h"

#include "MathUtils.h"
#include "Engine/Core/CoreMACROS.h"

STATIC const AABB3 AABB3::ZERO_TO_ONE = AABB3(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
STATIC const AABB3 AABB3::CENTER_PIVOT_UNIT_AABB = AABB3(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f);
STATIC const AABB3 AABB3::CENTER_PIVOT_AABB = AABB3(-10.0f, -10.0f, -10.0f, 10.0f, 10.0f, 10.0f);

AABB3::AABB3(const Vec3& center, float radiusX, float radiusY, float radiusZ)
{
	m_Maxs.m_X = center.m_X + radiusX;
	m_Maxs.m_Y = center.m_Y + radiusY;
	m_Maxs.m_Z = center.m_Z + radiusZ;

	m_Mins.m_X = center.m_X - radiusX;
	m_Mins.m_Y = center.m_Y - radiusY;
	m_Mins.m_Z = center.m_Z - radiusZ;
}

AABB3::AABB3(const AABB3& aabb)
	:m_Mins(aabb.m_Mins), m_Maxs(aabb.m_Maxs)
{

}

AABB3::~AABB3()
{
}

Vec3 AABB3::GetNearestPoint(const Vec3& position)
{
	float x = Clamp(position.m_X, m_Mins.m_X, m_Maxs.m_X);
	float y = Clamp(position.m_Y, m_Mins.m_Y, m_Maxs.m_Y);
	float z = Clamp(position.m_Z, m_Mins.m_Z, m_Maxs.m_Z);

	return Vec3(x, y, z);
}

Vec3 AABB3::GetDimensions() const
{
	float width = m_Maxs.m_X - m_Mins.m_X;
	float height = m_Maxs.m_Y - m_Mins.m_Y;
	float depth = m_Maxs.m_Z - m_Mins.m_Z;

	return Vec3(width, height, depth);
}

Vec3 AABB3::GetCenter() const
{
	float x = (m_Mins.m_X + m_Maxs.m_X) * 0.5f;
	float y = (m_Mins.m_Y + m_Maxs.m_Y) * 0.5f;
	float z = (m_Mins.m_Z + m_Maxs.m_Z) * 0.5f;

	return Vec3(x, y, z);
}

AABB3 AABB3::operator+(const Vec3& translation)
{
	AABB3 temp;

	temp.m_Mins = m_Mins + translation;
	temp.m_Maxs = m_Maxs + translation;

	return temp;
}

AABB3 AABB3::operator-(const Vec3& translation)
{
	AABB3 temp;

	temp.m_Mins = m_Mins - translation;
	temp.m_Maxs = m_Maxs - translation;
	
	return temp;
}