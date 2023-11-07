#pragma once

#include "../ofApp.h"
#include "Vector3D.h"

class Quaternion {

private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;

	Vector3D m_v;

	void fixFloat();
public:

	Quaternion(const float w = 0, const float x = 0, const float y = 0, const float z = 0);
	Quaternion(const float w, const Vector3D& v);
	~Quaternion();

	static Quaternion& Euler(const float detax, const float detay, const float detaz);
	static Quaternion& Identity();

	float Norm() const;
	Quaternion& Negation()const;
	Quaternion& Inverse()const;
	Quaternion& Conjugue()const;

	Quaternion& operator=(const Quaternion& q);
	Quaternion& operator*(const float f) const;
	Quaternion& operator*(const Quaternion& q) const;
	Quaternion& operator-(const Quaternion& q) const;
	float dot(Quaternion& q)const;
	Quaternion& operator^(const float exp)const;
	bool operator==(const Quaternion& q)const;

	bool EqualsWithTolerance(const Quaternion& q, const float tolerance = 1e-7) const;

	string toString() const;

	float getW()const;
	float getX()const;
	float getY()const;
	float getZ()const;
	Vector3D getVector()const;
};