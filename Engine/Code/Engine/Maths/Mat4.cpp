#include "Mat4.h"

#include "MathUtils.h"

inline Mat4::Mat4(float* matrixValues)
{
	Ix = *(matrixValues);  
	Iy = *(matrixValues + 1);
	Iz = *(matrixValues + 2);
	Iw = *(matrixValues + 3);
	Jx = *(matrixValues + 4);
	Jy = *(matrixValues + 5);
	Jz = *(matrixValues + 6);
	Jw = *(matrixValues + 7);
	Kx = *(matrixValues + 8);
	Ky = *(matrixValues + 9);
	Kz = *(matrixValues + 10);
	Kw = *(matrixValues + 11);
	Tx = *(matrixValues + 12);
	Ty = *(matrixValues + 13);
	Tz = *(matrixValues + 14);
	Tw = *(matrixValues + 15);
}

Mat4 Mat4::Inverse(const Mat4& matrix)
{
	Mat4 result;
	double det;
	double inv[4 * 4];
	double m[4 * 4];
	unsigned int index;

	for (index = 0; index < 16; index++)
	{
		m[index] = (double)matrix.elements[index];
	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	det = 1.0 / det;

	for (index = 0; index < 16; index++) {
		result.elements[index] = (float)(inv[index] * det);
	}

	return result;
}

Mat4& Mat4::Multiply(const Mat4& other)
{
	Ix = (Ix * other.Ix) + (Jx * other.Iy) + (Kx * other.Iz) + (Tx * other.Iw);
	Iy = (Iy * other.Ix) + (Jy * other.Iy) + (Ky * other.Iz) + (Ty * other.Iw);
	Iz = (Iz * other.Ix) + (Jz * other.Iy) + (Kz * other.Iz) + (Tz * other.Iw);
	Iw = (Iw * other.Ix) + (Jw * other.Iy) + (Kw * other.Iz) + (Tw * other.Iw);

	Jx = (Ix * other.Jx) + (Jx * other.Jy) + (Kx * other.Jz) + (Tx * other.Jw);
	Jy = (Iy * other.Jx) + (Jy * other.Jy) + (Ky * other.Jz) + (Ty * other.Jw);
	Jz = (Iz * other.Jx) + (Jz * other.Jy) + (Kz * other.Jz) + (Tz * other.Jw);
	Jw = (Iw * other.Jx) + (Jw * other.Jy) + (Kw * other.Jz) + (Tw * other.Jw);
	
	Kx = (Ix * other.Kx) + (Jx * other.Ky) + (Kx * other.Kz) + (Tx * other.Kw);
	Ky = (Iy * other.Kx) + (Jy * other.Ky) + (Ky * other.Kz) + (Ty * other.Kw);
	Kz = (Iz * other.Kx) + (Jz * other.Ky) + (Kz * other.Kz) + (Tz * other.Kw);
	Kw = (Iw * other.Kx) + (Jw * other.Ky) + (Kw * other.Kz) + (Tw * other.Kw);

	Tx = (Ix * other.Tx) + (Jx * other.Ty) + (Kx * other.Tz) + (Tx * other.Tw);
	Ty = (Iy * other.Tx) + (Jy * other.Ty) + (Ky * other.Tz) + (Ty * other.Tw);
	Tz = (Iz * other.Tx) + (Jz * other.Ty) + (Kz * other.Tz) + (Tz * other.Tw);
	Tw = (Iw * other.Tx) + (Jw * other.Ty) + (Kw * other.Tz) + (Tw * other.Tw);

	return *this;
}

void Mat4::Transpose()
{
	float values[] = {	Ix, Jx, Kx, Tx,     
						Iy, Jy, Ky, Ty, 
						Iz, Jz, Kz, Tz,
						Iw, Jw, Kw, Tw };

	*this = Mat4(values);
}

Mat4& Mat4::operator*(const Mat4& other)
{
	return Multiply(other);
}

Mat4& Mat4::operator*=(const Mat4& other)
{
	return Multiply(other);
}

bool Mat4::operator==(const Mat4& other)
{
	int c = 0;
	for (int i = 0; i < 4 * 4; i++)
	{
		if (elements[i] == other.elements[i])
			c = 0;
		else
			c++;
	}

	if (!c)
		return true;
	return false;
}

bool Mat4::operator!=(const Mat4& other)
{
	int c = 0;
	for (int i = 0; i < 4 * 4; i++)
	{
		if (elements[i] != other.elements[i])
			c = 0;
		else
			c++;
	}

	if (!c)
		return true;
	return false;
}

Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4 result;

	result.Ix = 2.0f / (right - left);
	result.Jy = 2.0f / (top - bottom);
	result.Kz = 2.0f / (far - near);
	result.Tx = (right + left) / (left - right);
	result.Ty = (top + bottom) / (bottom - top);
	result.Tz = (far + near) / (near - far);
	result.Tw = 1.0f;

	return result;
}

Mat4 Mat4::Perspective(float fov, float aspectRatio, float near, float far)
{//todo update edge cases
	Mat4 result;

	float q = 1.0f / TanDegrees(0.5f * fov);
	float range = far - near;
	float a = q * aspectRatio;

	if(aspectRatio > 1.0f)
	{
		a = q / aspectRatio;
	}

	float b = -far / range;
	float c = (far * near) / range;

	float proj[] = {
		   a,          0.0f,			  0.0f,						0.0f,
		0.0f,	          q,			  0.0f,						0.0f,
		0.0f,          0.0f,                 b,		                   c,
		0.0f,          0.0f,	         -1.0f,					    0.0f
	};

	return Mat4(proj);
}

Mat4 Mat4::Translation(const Vec3& translation)
{
	Mat4 result;
	result = Identity();
	
	result.Tx = translation.m_X;
	result.Ty = translation.m_Y;
	result.Tz = translation.m_Z;

	return result;
}

Mat4 Mat4::Rotation2D(float angle)
{
	Mat4 result;

	float cosValue = CosDegrees(angle);
	float sinValue = SinDegrees(angle);

	result.Ix =  cosValue;
	result.Iy =  sinValue;
						  
	result.Jx =  -sinValue;
	result.Jy =  cosValue;

	return result;
}

Mat4 Mat4::RotationX3D(float rotateX)
{
	Mat4 result;

	float cosValue = CosDegrees(rotateX);
	float sinValue = SinDegrees(rotateX);

	result.Jy = cosValue;
	result.Jz = sinValue;

	result.Ky = -sinValue;
	result.Kz = cosValue;

	return result;
}

Mat4 Mat4::RotationY3D(float rotateY)
{
Mat4 result;

	float cosValue = CosDegrees(rotateY);
	float sinValue = SinDegrees(rotateY);

	result.Ix = cosValue;
	result.Iz = -sinValue;

	result.Kx = sinValue;
	result.Kz = cosValue;

	return result;
}

Mat4 Mat4::RotationZ3D(float rotateZ)
{
	return Rotation2D(rotateZ);
}

Mat4 Mat4::Rotation3D(float x, float y, float z)
{
	return RotationY3D(y) * RotationX3D(x) * RotationZ3D(z);
}

Mat4 Mat4::Scale(const Vec3& scale)
{
	Mat4 result;

	result.Ix = scale.m_X;
	result.Jy = scale.m_Y;
	result.Kz = scale.m_Z;
	result.Tw = 1.0f;

	return result;
}

Mat4 Mat4::InvertFast(Mat4& matrix)
{
	Mat4 rotationTranspose = matrix;
	rotationTranspose.Tx = 0.0f;
	rotationTranspose.Ty = 0.0f;
	rotationTranspose.Tz = 0.0f;
	rotationTranspose.Transpose();

	Vec3 translation(-matrix.Tx, -matrix.Ty, -matrix.Tz);

	rotationTranspose.Tx = DotProduct(translation, Vec3(matrix.Ix,matrix.Iy,matrix.Iz).GetNormalised());
	rotationTranspose.Ty = DotProduct(translation, Vec3(matrix.Jx,matrix.Jy,matrix.Jz).GetNormalised());
	rotationTranspose.Tz = DotProduct(translation, Vec3(matrix.Kx,matrix.Ky,matrix.Kz).GetNormalised());

	Mat4 inverted = rotationTranspose;

	return inverted;
}
