#include "Vector3D.h"

Vector3D::Vector3D(const float x, const float y, const float z, const float w)
	:
	m_x(x),
	m_y(y),
	m_z(z),  // w is currently set to 0 because the vectors used are for a 3-dimensional space
	m_w(w)
{ 
	fixFloat();
}

Vector3D::Vector3D(glm::vec3 vector) 
{
	m_x = vector.x;		
	m_y = vector.y;		
	m_z = vector.z;		
	m_w = 0;		
};

Vector3D::~Vector3D() {}


Vector3D & Vector3D::operator+(const Vector3D& vector) const
{
	return Vector3D(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}


void Vector3D::operator+=(const Vector3D& vector)
{
	m_x += vector.m_x;
	m_y += vector.m_y;
	m_z += vector.m_z;
	fixFloat();
}


Vector3D & Vector3D::operator-(const Vector3D& vector) const
{
	return Vector3D(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
}


void Vector3D::operator-=(const Vector3D& vector)
{
	m_x -= vector.m_x;
	m_y -= vector.m_y;
	m_z -= vector.m_z;
	fixFloat();
}


Vector3D & Vector3D::operator*(const float val) const
{
	return Vector3D(val * m_x, val * m_y, val * m_z);
}


float Vector3D::operator*(const Vector3D& vector) const
{
	return m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z;
}


Vector3D & Vector3D::operator^(const Vector3D& vector) const
{
	return Vector3D(m_y * vector.m_z - m_z * vector.m_y,
		m_z * vector.m_x - m_x * vector.m_z,
		m_x * vector.m_y - m_y * vector.m_x);
}


bool Vector3D::operator==(const Vector3D& vector) const
{
	return this->m_x == vector.m_x && this->m_y == vector.m_y && this->m_z == vector.m_z && this->m_w == vector.m_w;
}

Vector3D& Vector3D::operator=(const Vector3D vector)
{
	this->m_x = vector.m_x;
	this->m_y = vector.m_y;
	this->m_z = vector.m_z;
	this->m_w = vector.m_w;
	
	return *this;
}

float Vector3D::Norm()
{
	return sqrt(pow(m_x,2) + pow(m_y, 2) + pow(m_z, 2));
}


float Vector3D::Norm2()
{
	return pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2);
}


void Vector3D::Normalize()
{
	if(!(*this == Vector3D()))
	{
		float norm = this->Norm();
		m_x /= norm;
		m_y /= norm;
		m_z /= norm;
		fixFloat();
	}
}

float Vector3D::distance(const Vector3D& vector)
{
	return (*this - vector).Norm();
}

string Vector3D::toString() const
{
	return "( " + to_string(m_x) + ", "
		+ to_string(m_y) + ", "
		+ to_string(m_z) + " )";
}

float Vector3D::x()const { return m_x; }
void Vector3D::x(float f) { m_x = f; }
float Vector3D::y()const { return m_y; }
void Vector3D::y(float f) { m_y = f; }
float Vector3D::z()const { return m_z; }
void Vector3D::z(float f) { m_z = f; }
float Vector3D::w()const { return m_w; }
void Vector3D::w(float f) { m_w = f; }

float& Vector3D::operator[](int i)
{
	switch (i)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	case 3: return m_w;
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
	case 3: return m_w;
	default: throw std::out_of_range("Bad idx passed to at()");
	}
}

void Vector3D::fixFloat()
{
	if (abs(m_x) < 10e-10) m_x = .0f;
	if (abs(m_y) < 10e-10) m_y = .0f;
	if (abs(m_z) < 10e-10) m_z = .0f;
	if (abs(m_w) < 10e-10) m_w = .0f;
}
