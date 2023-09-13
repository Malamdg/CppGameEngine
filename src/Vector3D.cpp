#include "Vector3D.h"


Vector3D::Vector3D(const float x, const float y, const float z)
	:
	m_x(x),
	m_y(y),
	m_z(z),
	m_w(0)
{ }

Vector3D::~Vector3D() {}

Vector3D & Vector3D::operator+(const Vector3D vector) const
{
	return Vector3D(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}
void Vector3D::operator+=(const Vector3D vector)
{
	m_x += vector.m_x;
	m_y += vector.m_y;
	m_z += vector.m_z;
}
Vector3D & Vector3D::operator-(const Vector3D vector) const
{
	return Vector3D(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
}
void Vector3D::operator-=(const Vector3D vector)
{
	m_x -= vector.m_x;
	m_y -= vector.m_y;
	m_z -= vector.m_z;
}
Vector3D & Vector3D::operator*(const float val) const
{
	return Vector3D(val * m_x, val * m_y, val * m_z);
}
float Vector3D::operator*(const Vector3D vector) const
{
	return m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z;
}
Vector3D & Vector3D::operator^(const Vector3D vector) const
{
	return Vector3D(m_y * vector.m_z - m_z * vector.m_y,
		m_z * vector.m_x - m_x * vector.m_z,
		m_y * vector.m_x - m_x * vector.m_y);
}

float Vector3D::Norm()
{
	return sqrt(pow(m_x,2) + pow(m_z, 2) + pow(m_z, 2));
}

float Vector3D::Norm2()
{
	return pow(m_x, 2) + pow(m_z, 2) + pow(m_z, 2);
}

void Vector3D::Normalize()
{
	float norm = this->Norm();
	m_x /= norm;
	m_y /= norm;
	m_z /= norm;
}

float& Vector3D::operator[](int i)
{
	switch (i)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	default: throw std::out_of_range("Bad idx passed to at()");
	}
}
const float& Vector3D::operator[](int i) const
{
	switch (i)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	default: throw std::out_of_range("Bad idx passed to at()");
	}
}