#pragma once

#include "Vec3.h"

class AABB3
{
public:
	Vec3 m_Mins;
	Vec3 m_Maxs;
	
	static const AABB3 ZERO_TO_ONE;
	static const AABB3 CENTER_PIVOT_UNIT_AABB;
	static const AABB3 CENTER_PIVOT_AABB;
public:
	constexpr AABB3() = default;
	explicit AABB3(float minX, float minY, float minZ, float maxX, float maxY, float maxZ): m_Mins(Vec3(minX, minY, minZ)), m_Maxs(Vec3(maxX, maxY, maxZ)) {}
	explicit AABB3(const Vec3& mins, const Vec3& maxs): m_Mins(mins), m_Maxs(maxs) {}
	explicit AABB3(const Vec3& center, float radiusX, float radiusY, float radiusZ);
	AABB3(const AABB3& aabb);
	~AABB3();

	Vec3 GetNearestPoint(const Vec3& position);
	Vec3 GetDimensions() const;
	Vec3 GetCenter() const;

	AABB3 operator +(const Vec3& translation);
	AABB3 operator -(const Vec3& translation);
};
