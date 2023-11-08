#pragma once

#include "Vector3D.h"

class Matrix3 
{
private:
	// Coefficients of the matrix
	float m_coefficients[3][3];

	// Determinent of the matrix
	float m_det;

	// Calculate the determinent and store the value in m_det
	void updateDet();

public:
	// Constant size of lines and columns
	static const int m_size = 3;
	
	// Constructors

	/*
	* Constructor from Vector3D, can be used as an empty constructor
	*/
	Matrix3(Vector3D column1 = Vector3D(), Vector3D column2 = Vector3D(), Vector3D column3 = Vector3D());
	
	/*
	* Constructor from float array array
	*/
	Matrix3(float coefficients[3][3]);

	/*
	* Constructor from const float array array
	*/
	Matrix3(const float coefficients[3][3]);

	/*
	* Destructor of class
	*/
	~Matrix3();

	// Basic matrices
	static Matrix3 identity();
	static Matrix3 zeros();

	// Basic operation on matrix
	
	/*
	* Get determinant of this
	*/
	float det();
	
	/*
	* Method to invert this
	*/
	void invert();
	
	/*
	* Function to get the inverse of this
	*/
	Matrix3 inverse();
	
	/*
	* Method to transpose this
	*/
	void transpose();

	/*
	* Function to get transposed this
	*/
	Matrix3 transposedMatrix();

	// Operations between matrix and other
	
	/*
	* Basic operator for the sum between two Matrix3
	*/
	Matrix3& operator+(const Matrix3& matrix) const;
	
	/*
	* Basic operator for the difference between two Matrix3
	*/
	Matrix3& operator-(const Matrix3& matrix) const;
	
	/*
	* Basic operator for the product of two Matrix3
	*/
	Matrix3& operator*(const Matrix3& matrix) const;

	/*
	* Basic operator for the product of a Matrix3 by a scalar
	*/
	Matrix3& operator*(const float& lambda) const;

	/*
	* Basic operator for the product of a Vector3D by a Matrix3
	*/
	Vector3D& operator*(const Vector3D& v) const;

	// Affect operation
	
	/*
	* Affects the value of the sum with another Matrix3 to this
	*/
	void operator+=(const Matrix3& matrix);
	
	/*
	* Affects the value of the difference between this and another Matrix3 to this
	*/
	void operator-=(const Matrix3& matrix);


	/*
	* Affects the value of the product (right side) of this and another Matrix3 to this
	* i.e. this = this * matrix
	*/
	void operator*=(const Matrix3& matrix);

	/*
	* Affects the value of the product of this by a scalar to this  	
	*/
	void operator*=(const float& lambda);
	
	// Equality test

	/*
	* Return whether matrices are equal in value or not
	*/
	bool operator==(const Matrix3& matrix);

	// Accessors
	
	/*
	* Setter accessor for the indexed line
	*/
	float* operator[](int i);


	/*
	* Getter accessor for the indexed line
	*/
	const float* operator[](int i) const;
};