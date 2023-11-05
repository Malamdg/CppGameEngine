#pragma once

#include "ofApp.h"

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
	Quaternion(const float w = 0, const Vector3D& v = Vector3D());
	~Quaternion();

	static Quaternion& Euler(const float detax, const float detay, const float detaz);
	static Quaternion& Identity();

	float Norme() const;
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
};