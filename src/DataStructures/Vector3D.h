#pragma once

#include "OfMain.h";

class Vector3D {

private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
	

public: 
	
	/*
	class constructor

	@param x the abscissa
	@param y the ordinate
	@param z the depth
	*/
	Vector3D(const float x = 0, const float y = 0, const float z = 0, const float w = 0);
	Vector3D(glm::vec3 vector);
	~Vector3D();

	/*
	definition of operator +
	allows to sum two vectors

	@param vector, the vector added to the one to which the operation applies

	@return the sum of the two vectors
	*/
	Vector3D& operator+(const Vector3D& vector) const;

	/*
	definition of operator +=
	allows to add a vector to the one to which the operation applies

	@param vector, the vector added to the one to which the operation applies
	*/
	void operator+=(const Vector3D& vector);

	/*
	definition of operator -
	allows to substract two vectors

	@param vector, the vector substracted to the one to which the operation applies
	*/
	Vector3D& operator-(const Vector3D& vector) const;

	/*
	definition of operator -=
	allows to substract a vector to the one to which the operation applies

	@param vector, the vector substracted to the one to which the operation applies

	@return the difference of the two vectors
	*/
	void operator-=(const Vector3D& vector);

	/*
	definition of operator *
	allows to do the product of a vector and a value

	@param val, the value multiplied to the vector

	@return the product
	*/
	Vector3D& operator*(const float val) const;

	/*
	definition of operator *
	allows to do the scalar product of two vectors

	@param vector, the vector multiplied to the one to which the operation applies

	@return the scalar product of the two vectors
	*/
	float operator*(const Vector3D& vector) const;

	/*
	definition of operator ^
	allows to do the cross product of two vectors

	@param vector, the vector multiplied to the one to which the operation applies

	@return the cross product of the two vectors
	*/
	Vector3D& operator^(const Vector3D& vector) const;

	/*
	definition of operator ==
	allows to test the equality between two vectors

	@param vector, the vector compared to the one to which the operation applies

	@return true if the vectors are the same
	*/
	bool operator==(const Vector3D& vector) const;

	Vector3D& operator=(const Vector3D vector);

	/*
	definition of the norm (here norm2)
	allows to do compute the norm of a vector

	@return the vector's norm
	*/
	float Norm();

	/*
	definition of the norm2
	allows to do compute the norm 2 of a vector

	@return the vector's norm 2
	*/
	float Norm2();

	/*
	normalization
	normalize a vector in place
	*/
	void Normalize();

	/*
	deistance between two vector
	
	@return the distance between this vector and the one passed in parameters
	*/
	float distance(const Vector3D& vector);

	/*
	convert a vector to string

	@return a string description of the vector
	*/
	string toString() const;

	/*
	get the x component of a vector
 
	@return the component
	*/
	float x()const;

	/*
	set the x component of a vector

 	@param f, the new value for the component
	*/
	void x(float f);

	/*
	get the y component of a vector
 
	@return the component
	*/
	float y()const;

	/*
	set the y component of a vector

 	@param f, the new value for the component
	*/
	void y(float f);

	/*
	get the z component of a vector
 
	@return the component
	*/
	float z()const;

	/*
	set the z component of a vector

 	@param f, the new value for the component
	*/
	void z(float f);
  
	/*
	get the w component of a vector

	@return the component
	*/
	float w()const;

	/*
	set the w component of a vector

	@param f, the new value for the component
	*/
	void w(float f);

	/*
	set the component of a vector
	set the i-th coordinate of the vector

	@return the component
	*/
	float& operator[](int i);

	/*
	get the component of a vector
	get the i-th coordinate of the vector

	@return the component
	*/
	const float& operator[](int i) const;

	glm::vec2 v2() { return glm::vec2(m_x, m_y); };
	glm::vec3 v3() { return glm::vec3(m_x, m_y, m_z); };


	void fixFloat();
};
