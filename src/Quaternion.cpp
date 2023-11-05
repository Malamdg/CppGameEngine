#include "Quaternion.h"

void Quaternion::fixFloat()
{
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
	Quaternion qx = Quaternion(cos(tetax / 2), sin(tetax / 2), 0, 0);
	Quaternion qy = Quaternion(cos(tetay / 2), 0, sin(tetay / 2), 0);
	Quaternion qz = Quaternion(cos(tetaz / 2), 0, 0, sin(tetaz / 2));
	return qx * qy * qz;
}

Quaternion& Quaternion::Identity()
{
	return Quaternion(1, 0, 0, 0);
}

float Quaternion::Norme() const
{
	return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

Quaternion& Quaternion::Negation()const
{
	return Quaternion(-m_w, -m_x, -m_y, -m_z);
}

Quaternion& Quaternion::Inverse()const
{
	if(Norme() == 0) throw std::exception("Inverse doesn't exist for this Quaternion - null Norm Exception");
	return Conjugue() * (1 / Norme());
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
	Vector3D resv = q.m_v * m_w + m_v * q.m_w + m_v ^ q.m_v;

	return Quaternion(resw, resv);
}

Quaternion& Quaternion::operator-(const Quaternion& q) const
{
	return q * Conjugue();
}

float Quaternion::dot(Quaternion& q)const
{
	return m_w * q.m_w + m_x * q.m_x + m_y * q.m_y + m_z * q.m_z;
}

Quaternion& Quaternion::operator^(const float exp)const
{
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