#include "Vec3.h"

#include "Engine/Core/CoreMACROS.h"
#include "MathUtils.h"

STATIC const Vec3 Vec3::ZERO;
STATIC const Vec3 Vec3::ONE = Vec3(1.0f, 1.0f, 1.0f);
STATIC const Vec3 Vec3::UNIT_X = Vec3(1.0f, 0.0f, 0.0f);
STATIC const Vec3 Vec3::UNIT_Y = Vec3(0.0f, 1.0f, 0.0f);
STATIC const Vec3 Vec3::UNIT_Z = Vec3(0.0f, 0.0f, 1.0f);

Vec3::Vec3()
	: m_X(0), m_Y(0), m_Z(0)
{
}

Vec3::Vec3(float x, float y, float z)
	: m_X(x), m_Y(y), m_Z(z)
{
}

Vec3 Vec3::operator+(const Vec3& other)
{
	return Vec3(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
}

Vec3 Vec3::operator-(const Vec3& other)
{
	return Vec3(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
}

Vec3 Vec3::operator*(const Vec3& other)
{
	return Vec3(m_X * other.m_X, m_Y * other.m_Y, m_Z * other.m_Z);
}

Vec3 Vec3::operator/(const Vec3& other)
{
	return Vec3(m_X / other.m_X, m_Y / other.m_Y, m_Z / other.m_Z);
}

Vec3& Vec3::operator+=(const Vec3& other)
{
	m_X += other.m_X;
	m_Y += other.m_Y;
	m_Z += other.m_Z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
	m_X -= other.m_X;
	m_Y -= other.m_Y;
	m_Z -= other.m_Z;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& other)
{
	m_X *= other.m_X;
	m_Y *= other.m_Y;
	m_Z *= other.m_Z;
	return *this;
}

Vec3& Vec3::operator/=(const Vec3& other)
{
	m_X /= other.m_X;
	m_Y /= other.m_Y;
	m_Z /= other.m_Z;
	return *this;
}

bool Vec3::operator==(const Vec3& other)
{
	return this->m_X == other.m_X && this->m_Y == other.m_Y && this->m_Z == other.m_Z;
}

bool Vec3::operator!=(const Vec3& other)
{
	return !(*this == other);
}

float Vec3::GetLength() const
{
	return sqrtf((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));
}

Vec3 Vec3::GetNormalised() const
{
	Vec3 temp;
	float length = GetLength();
	temp.m_X = m_X / length;
	temp.m_Y = m_Y / length;
	temp.m_Z = m_Z / length;
	return temp; 
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
{
	stream << "(" << vector.m_X << ", " << vector.m_Y << ", " << vector.m_Z << ")";
	return stream;
}

Vec3 Interpolate(const Vec3& start, const Vec3& end, float delta)
{
	Vec3 temp;

	temp.m_X = Interpolate(start.m_X, end.m_X, delta);
	temp.m_Y = Interpolate(start.m_Y, end.m_Y, delta);
	temp.m_Z = Interpolate(start.m_Z, end.m_Z, delta);

	return temp;
}
