#include "Vector3D.h"

/*
class constructor
w is currently set to 0 because the vectors used are for a 3-dimensional space
*/
Vector3D::Vector3D(const float x, const float y, const float z)
	:
	m_x(x),
	m_y(y),
	m_z(z),
	m_w(0)
{ }

Vector3D::~Vector3D() {}

/*
definition of operator +
allows to sum two vectors

@param vector, the vector added to the one to which the operation applies

@return the sum of the two vectors
*/
Vector3D & Vector3D::operator+(const Vector3D vector) const
{
	return Vector3D(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}

/*
definition of operator +=
allows to add a vector to the one to which the operation applies

@param vector, the vector added to the one to which the operation applies
*/
void Vector3D::operator+=(const Vector3D vector)
{
	m_x += vector.m_x;
	m_y += vector.m_y;
	m_z += vector.m_z;
}

/*
definition of operator -
allows to substract two vectors

@param vector, the vector substracted to the one to which the operation applies
*/
Vector3D & Vector3D::operator-(const Vector3D vector) const
{
	return Vector3D(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
}

/*
definition of operator -=
allows to substract a vector to the one to which the operation applies

@param vector, the vector substracted to the one to which the operation applies

@return the difference of the two vectors
*/
void Vector3D::operator-=(const Vector3D vector)
{
	m_x -= vector.m_x;
	m_y -= vector.m_y;
	m_z -= vector.m_z;
}

/*
definition of operator *
allows to do the product of a vector and a value

@param val, the value multiplied to the vector

@return the product
*/
Vector3D & Vector3D::operator*(const float val) const
{
	return Vector3D(val * m_x, val * m_y, val * m_z);
}

/*
definition of operator *
allows to do the scalar product of two vectors

@param vector, the vector multiplied to the one to which the operation applies

@return the scalar product of the two vectors
*/
float Vector3D::operator*(const Vector3D vector) const
{
	return m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z;
}

/*
definition of operator ^
allows to do the cross product of two vectors

@param vector, the vector multiplied to the one to which the operation applies

@return the cross product of the two vectors
*/
Vector3D & Vector3D::operator^(const Vector3D vector) const
{
	return Vector3D(m_y * vector.m_z - m_z * vector.m_y,
		m_z * vector.m_x - m_x * vector.m_z,
		m_x * vector.m_y - m_y * vector.m_x);
}

/*
definition of the norm (here norm2)
allows to do compute the norm of a vector

@return the vector's norm
*/
float Vector3D::Norm()
{
	return sqrt(pow(m_x,2) + pow(m_y, 2) + pow(m_z, 2));
}

/*
definition of the norm2
allows to do compute the norm 2 of a vector

@return the vector's norm 2
*/
float Vector3D::Norm2()
{
	return pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2);
}

/*
normalization
normalize a vector in place
*/
void Vector3D::Normalize()
{
	float norm = this->Norm();
	m_x /= norm;
	m_y /= norm;
	m_z /= norm;
}

/*
convert a vector to string

@return a string description of the vector
*/
string Vector3D::toString() const
{
	return "( " + to_string(m_x) + ", "
		+ to_string(m_y) + ", "
		+ to_string(m_z) + " )";
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
