#pragma once

#include "OfMain.h";

class Vector3D {

private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
	

public: 
	

	Vector3D(const float x = 0, const float y = 0, const float z = 0);
	~Vector3D();

	Vector3D& operator+(const Vector3D vector) const;
	void operator+=(const Vector3D vector);
	Vector3D& operator-(const Vector3D vector) const;
	void operator-=(const Vector3D vector);
	Vector3D& operator*(const float val) const;
	float operator*(const Vector3D vector) const;
	Vector3D& operator^(const Vector3D vector) const;

	float Norm();
	float Norm2();
	void Normalize();

	string toString() const;

	float& operator[](int i);
	const float& operator[](int i) const;

	glm::vec2 v2() { return glm::vec2(m_x, m_y); };
	glm::vec3 v3() { return glm::vec3(m_x, m_y, m_z); };

};