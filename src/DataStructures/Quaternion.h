#pragma once

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
	/*
	class constructor

	@param w, the first coordinate of the quaternion
	@param x, the second coordinate of the quaternion
	@param y, the third coordinate of the quaternion
	@param z, the fourth coordinate of the quaternion
	*/
	Quaternion(const float w = 0, const float x = 0, const float y = 0, const float z = 0);
	/*
	class constructor

	@param w, the first coordinate of the quaternion
	@param v, a vector 3D for the 3 remaining coordinates
	*/
	Quaternion(const float w, const Vector3D& v);
	/*
	class destructor
	*/
	~Quaternion();

	/*
	Create a quaternion from a rotation

	@param detax, rotation according to the first axis
	@param detay, rotation according to the second axis
	@param detaz, rotation according to the third axis
	@return quaternion associated to the rotation
	*/
	static Quaternion& Euler(const float detax, const float detay, const float detaz);
	/*
	Create the identity quaternion
	The identity is (1, 0, 0, 0)
	@return identity
	*/
	static Quaternion& Identity();
	
	/*
	Spherical Linear Interpolation of two Quaternions
 
 	@param q0, the first quaternion
	@param q1, the second quaternion
 	@param t, fraction to keep
 	@return the queternion interpolated
	*/
	static Quaternion& slerp(const Quaternion& q0, const Quaternion& q1, const float t);

	/*
	Compute the Norm

	@return, the norm of the quaternion
	*/
	float Norm() const;

	void Normalize();
	/*
	Compute the negation of the Quaternion

	@return the negation
	*/
	Quaternion& Negation()const;
	/*
	Compute the inverse of the Quaternion

	@return the inverse
	*/
	Quaternion& Inverse()const;
	/*
	Compute the conjugate of the Quaternion

	@return the conjugate
	*/
	Quaternion& Conjugue()const;

	/*
	Assign the value of a quaternion to the current one

	@param q, a quaternion
	@return the modified quaternion
	*/
	Quaternion& operator=(const Quaternion& q);
	/*
	Define the operator * between a quaternion and a float

	@param f, the float for the product
	@return the product
	*/
	Quaternion& operator*(const float f) const;
	/*
	Define the cross product between two quaternions

	@param q, the quaternion for the product
	@return the result of the cross product
	*/
	Quaternion& operator*(const Quaternion& q) const;
	/*
	Define the operator + between two quaternions

	@param q, the quaternion for the sum
	@return the sum
	*/
	Quaternion& operator+(const Quaternion& q) const;
	/*
	Define the operator - between two quaternions

	@param q, the quaternion for the substraction
	@return the difference
	*/
	Quaternion& operator-(const Quaternion& q) const;
	/*
	Define the scalar product between two quaternions

	@param q, the quaternion for the product
	@return the result of the scalar product
	*/
	float dot(Quaternion& q)const;
	/*
	Define the exponentiation for a quaternion

	@param q, the exponent
	@return the result of the exponentiation
	*/
	Quaternion& operator^(const float exp)const;
	/*
	Define the operator == between two quaternions

	@param q, the quaternion for the equality test
	@return test's result
	*/
	bool operator==(const Quaternion& q)const;

	/*
	Equality between quaternion with a tolerance to manage float approximation

	@param q, the quaternion for the equality test
	@param tolerance, the threshold for the tolerance
	@return test's result
	*/
	bool EqualsWithTolerance(const Quaternion& q, const float tolerance = 1e-7) const;

	/*
	Convert a quaternion to string

	@return text formatting for the quaternion
	*/
	string toString() const;

	/*
	getter for the w coordinate

	@return the w coordinate
	*/
	float getW()const;
	/*
	getter for the x coordinate

	@return the x coordinate
	*/
	float getX()const;
	/*
	getter for the y coordinate

	@return the y coordinate
	*/
	float getY()const;
	/*
	getter for the z coordinate

	@return the z coordinate
	*/
	float getZ()const;
	/*
	getter for the x,y,z Vector3D

	@return the Vector3D
	*/
	Vector3D getVector()const;

	glm::quat q() { return glm::quat(m_w, m_x, m_y, m_z); }
};
