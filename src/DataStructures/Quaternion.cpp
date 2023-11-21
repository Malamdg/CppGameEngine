#include "Quaternion.h"

void Quaternion::fixFloat()
{
	// threshold at 10e-10, under this value we consider that the coordinate is null
	if (abs(m_x) < 10e-10) m_x = .0f;
	if (abs(m_y) < 10e-10) m_y = .0f;
	if (abs(m_z) < 10e-10) m_z = .0f;
	if (abs(m_w) < 10e-10) m_w = .0f;
}


Quaternion::Quaternion(const float w, const float x, const float y, const float z)
	:
	m_x(x),
	m_y(y),
	m_z(z),
	m_w(w),
	m_v(Vector3D(m_x, m_y, m_z))
{
	fixFloat();
}

Quaternion::Quaternion(const float w, const Vector3D& v)
	:
	Quaternion(w, v[0], v[1], v[2])
{ }

Quaternion::~Quaternion() { }

Quaternion& Quaternion::Euler(const float tetax, const float tetay, const float tetaz)
{
	// compute the three coordinate of the quaternion according to the angle 
	Quaternion qx = Quaternion(cos(tetax / 2), sin(tetax / 2), 0, 0);
	Quaternion qy = Quaternion(cos(tetay / 2), 0, sin(tetay / 2), 0);
	Quaternion qz = Quaternion(cos(tetaz / 2), 0, 0, sin(tetaz / 2));
	
	Quaternion resq = qx * qy;
	resq = resq * qz;

	return resq;
}

Quaternion& Quaternion::Identity()
{
	return Quaternion(1, 0, 0, 0);
}

Quaternion& Quaternion::slerp(const Quaternion& q0, const Quaternion& q1, const float t)
{
	Quaternion inverseQ = q0.Inverse();
	Quaternion q = q1 * inverseQ;
	Quaternion expQ = q ^ t;

	return q0 * expQ;
}

float Quaternion::Norm() const
{
	return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

Quaternion& Quaternion::Negation()const
{
	return Quaternion(-m_w, -m_x, -m_y, -m_z);
}

Quaternion& Quaternion::Inverse()const
{
	if(Norm() == 0) throw std::exception("Inverse doesn't exist for this Quaternion - null Norm Exception");
	return Conjugue() * (1 / Norm());
}

Quaternion& Quaternion::Conjugue()const
{
	return Quaternion(m_w, -m_x, -m_y, -m_z);
}

Quaternion& Quaternion::operator*(const float f) const
{
	return Quaternion(m_w*f, m_x*f, m_y*f, m_z*f);
}

Quaternion& Quaternion::operator*(const Quaternion& q) const
{
	float resw = m_w * q.m_w - m_v * q.m_v;
	
	Vector3D v1 = (q.m_v * m_w);
	Vector3D v2 = (m_v * q.m_w);
	Vector3D v3 = (m_v ^ q.m_v);
	
	Vector3D resv = v1 + v2;
	resv = resv + v3;
	
	return Quaternion(resw, resv);
}

Quaternion& Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(m_w + q.m_w, m_x + q.m_x, m_y + q.m_y, m_z + q.m_z);
}

Quaternion& Quaternion::operator-(const Quaternion& q) const
{
	Quaternion conj = Conjugue();
	return q * conj;
}

float Quaternion::dot(Quaternion& q)const
{
	return m_w * q.m_w + m_x * q.m_x + m_y * q.m_y + m_z * q.m_z;
}

Quaternion& Quaternion::operator^(const float exp)const
{
	// C est une tolerance elevee mais c est ce qu il faut
	if (abs(Norm() - 1) > 10e-3) throw std::exception("Quaternion isn't a rotation - Current implementation do not consider exponentiation for Quaternion that are not roations");

	float a = acos(m_w);
	Vector3D resv = m_v * (sin(exp * a) / sin(a));
	return Quaternion(cos(exp * a), resv);
}

bool Quaternion::operator==(const Quaternion& q)const
{
	return m_w == q.m_w && m_x == q.m_x && m_y == q.m_y && m_z == q.m_z;
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	m_w = q.m_w;
	m_x = q.m_x;
	m_y = q.m_y;
	m_z = q.m_z;
	m_v = q.m_v;

	return *this;
}

bool Quaternion::EqualsWithTolerance(const Quaternion& q, const float tolerance) const
{
	return abs(m_w - q.m_w) < tolerance
		&& abs(m_x - q.m_x) < tolerance
		&& abs(m_y - q.m_y) < tolerance
		&& abs(m_z - q.m_z) < tolerance;
}


string Quaternion::toString() const
{
	return "(" + to_string(m_w) + ", "
		+ to_string(m_x) + ", "
		+ to_string(m_y) + ", "
		+ to_string(m_z) + ")";
}

float Quaternion::getW()const { return m_w; }
float Quaternion::getX()const { return m_x; }
float Quaternion::getY()const { return m_y; }
float Quaternion::getZ()const { return m_z; }
Vector3D Quaternion::getVector()const { return m_v; }

//Matrix3 Quaternion::matrixFromQuaternion() const
//{
//	float coefficient[9];
//
//	coefficient[0] = 1 - 2 * (m_y * m_y + m_z * m_z);
//	coefficient[1] = 2 * (m_x * m_y + m_z * m_w);
//	coefficient[2] = 2 * (m_x * m_z - m_y * m_w);
//	coefficient[3] = 2 * (m_x * m_y - m_z * m_w);
//	coefficient[4] = 1 - 2 * (m_x * m_x + m_z * m_z);
//	coefficient[5] = 2 * (m_y * m_z + m_x * m_w);
//	coefficient[6] = 2 * (m_x * m_z + m_y * m_w);
//	coefficient[7] = 2 * (m_y * m_z - m_z * m_w);
//	coefficient[8] = 1 - 2 * (m_x * m_x + m_y * m_y);
//
//	Matrix3 mq = Matrix3(coefficient);
//
//	return mq;
//}