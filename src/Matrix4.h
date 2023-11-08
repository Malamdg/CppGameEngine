#pragma once

#include "Vector3D.h"

class Matrix4
{
private:
	// Coefficients of the matrix
	float m_coefficients[4][4];

	// Determinent of the matrix
	float m_det;

	// Calculate the determinent and store the value in m_det
	void updateDet();

public:
	// Constant size of lines and columns
	static const int m_size = 4;
	
	// Constructors

	/*
	* Constructor from Vector3D, can be used as an empty constructor
	*/
	Matrix4(Vector3D column1 = Vector3D(), Vector3D column2 = Vector3D(), Vector3D column3 = Vector3D(), Vector3D column4 = Vector3D());
	
	/*
	* Constructor from float array array
	*/
	Matrix4(float coefficients[4][4]);

	/*
	* Constructor from const float array array
	*/
	Matrix4(const float coefficients[4][4]);

	/*
	* Destructor of class
	*/
	~Matrix4();

	// Basic matrices
	static Matrix4 identity();
	static Matrix4 zeros();

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
	Matrix4 inverse();
	
	/*
	* Method to transpose this
	*/
	void transpose();

	/*
	* Function to get transposed this
	*/
	Matrix4 transposedMatrix();

	// Operations between matrix and other
	
	/*
	* Basic operator for the sum between two Matrix4
	*/
	Matrix4& operator+(const Matrix4& matrix) const;
	
	/*
	* Basic operator for the difference between two Matrix4
	*/
	Matrix4& operator-(const Matrix4& matrix) const;
	
	/*
	* Basic operator for the product of two Matrix4
	*/
	Matrix4& operator*(const Matrix4& matrix) const;

	/*
	* Basic operator for the product of a Matrix4 by a scalar
	*/
	Matrix4& operator*(const float& lambda) const;

	// Affect operation
	
	/*
	* Affects the value of the sum with another Matrix4 to this
	*/
	void operator+=(const Matrix4& matrix);
	
	/*
	* Affects the value of the difference between this and another Matrix4 to this
	*/
	void operator-=(const Matrix4& matrix);


	/*
	* Affects the value of the product (right side) of this and another Matrix4 to this
	* i.e. this = this * matrix
	*/
	void operator*=(const Matrix4& matrix);

	/*
	* Affects the value of the product of this by a scalar to this  	
	*/
	void operator*=(const float& lambda);
	
	// Equality test

	/*
	* Return whether matrices are equal in value or not
	*/
	bool operator==(const Matrix4& matrix);

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