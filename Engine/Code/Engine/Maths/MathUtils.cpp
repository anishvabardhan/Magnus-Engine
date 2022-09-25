#include "MathUtils.h"

#include "AABB2.h"
#include "Maths_Func.h"
#include"Vec2.h"
#include "Vec3.h"

float Clamp(float value, float min, float max)
{
	if(value > max)
	{
		return max;
	}

	if(value < min)
	{
		return min;
	}
	
	return value;
}

float CosDegrees(float degrees)
{
	return cosf(toRadians(degrees));
}

float SinDegrees(float degrees)
{
	return sinf(toRadians(degrees));
}

float DotProduct(const Vec3& a, const Vec3& b)
{
    return ((a.m_X * b.m_X) + (a.m_Y * b.m_Y) + (a.m_Z * b.m_Z));
}

float TanDegrees(float degrees)
{
	return tanf(toRadians(degrees));
}

float Atan2Degrees(float y, float x)
{
	return toDegrees(atan2f(y, x));
}

float RangeMap(float inputValue, float inputBegin, float inputEnd, float outputBegin, float outputEnd)
{
	float inputRange = inputEnd - inputBegin;
	float outputRange = outputEnd - outputBegin;

	float inputRelative = inputValue - inputBegin;

	float inputRelativeFraction = inputRelative / inputRange;

	float outValue = (inputRelativeFraction * outputRange) + outputBegin;

	return outValue;
}

bool Disc_AABB2Collision(const Vec2& center, const float& radius, AABB2& box)
{
	Vec2 nearestPoint = box.GetNearestPoint(center);

	float distSquared = ((nearestPoint.m_X - center.m_X) * (nearestPoint.m_X - center.m_X)) + ((nearestPoint.m_Y - center.m_Y) * (nearestPoint.m_Y - center.m_Y));
	float radSquared = radius * radius;

	return (distSquared <= radSquared);
}

float Interpolate(const float& start, const float& end, float delta)
{
	float range = end - start;

	float fractionValue = delta * range;

	return fractionValue + start;
}