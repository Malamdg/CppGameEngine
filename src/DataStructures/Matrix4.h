#pragma once

#include "Matrix3.h"

class Matrix4
{
public:
	static const int m_size = 4;

	/*
	empty class constructor
	*/
	Matrix4();

	/*
	class constructor

	@param coeff[16], an array with the 16 coeffs, line by line
	*/
	Matrix4(float coeff[16]);

	/*
	class destructor
	*/
	~Matrix4();

	/*
	Create the matrix identity 
	The identity is :
 	1 0 0 0
  	0 1 0 0
	0 0 1 0
 	0 0 0 1
 
	@return identity
	*/
	static Matrix4 Identity();

	/*
	Create the null matrix 
 
	@return a matrix with all coeff set to 0
	*/
	static Matrix4 Zeros();

	/*
	Getter and Setter for a Matrix
	@param i, the line of the coeff searched
 	@param j, the column of the coeff searched

	@return the coeff 
	*/
	float& at(int i, int j);

	/*
	Getter for a Matrix
	@param i, the line of the coeff searched
 	@param j, the column of the coeff searched

	@return the coeff 
	*/
	const float& at(int i, int j) const;

	/*
	Product bewteen two Matrix
	@param m, the second matrix

	@return the product's result 
	*/
	Matrix4& operator*(const Matrix4& m) const;

	/*
	Product bewteen a Matrix and a float
	@param f, the float which multiplies the matrix

	@return the product's result 
	*/
	Matrix4& operator*(const float& f) const;

	/*
	Product bewteen a Matrix and a float
	@param v, the Vector3D which is multiplied by the matrix : matrix * v

	@return the product's result 
	*/
	Vector3D& operator*(const Vector3D& v) const;

	/*
	Sum of two Matrix
	@param m, the second matrix

	@return the sum's result 
	*/
	Matrix4& operator+(const Matrix4& m) const;

	/*
	Difference of two Matrix
	@param m, the second matrix

	@return the difference's result 
	*/
	Matrix4& operator-(const Matrix4& m) const;

	/*
	Test the equality of two Matrix
	@param m, the second matrix

	@return true if the matrix are the same
	*/
	bool operator==(const Matrix4& m) const;

	/*
	Test the non-equality of two Matrix
	@param m, the second matrix

	@return true if the matrix are not the same
	*/
	bool operator!=(const Matrix4& m) const;

	/*
	Redefinition of *= operator (in place product with a float)
	@param f, the float which multiplies the matrix
	*/
	void operator*=(const float& f);

	/*
	Redefinition of *= operator (in place product with a matrix)
	@param m, the other matrix
	*/
	void operator*=(const Matrix4& m);

	/*
	Redefinition of += operator (in place sum with a matrix)
	@param m, the other matrix
	*/
	void operator+=(const Matrix4& m);

	/*
	Redefinition of -= operator (in place difference with a matrix)
	@param m, the other matrix
	*/
	void operator-=(const Matrix4& m);

	/*
	To get the Determinant of a Matrix

 	@return the determinant 
	*/
	float getDeterminant();

	/*
	To inverse a Matrix in place 
	*/
	void invert();

	/*
	To get the inverse a Matrix

 	@return the Matrix's inverse 
	*/
	Matrix4 Inverse();

	/*
	To transpose a Matrix in place
	*/
	void transpose();

	/*
	To get the transpose of a Matrix

 	@return the Matrix's transpose 
	*/
	Matrix4 Transposed();

	/*
	To get the Matrix in string format (for dsiplay)

 	@return the Matrix's string 
	*/
	string toString() const;

	/*
	Compare two float according to a threshold
 	@param A, the first float
   	@param B, the second float
     	@param epsilon, the threshold
	*/
	static bool cmpf(float A, float B, float epsilon = 10e-5);
private:
	/*
	Matrix's coeffs
	*/
	float m_coeffs[16];

	/*
	To get the Matrix cofactor without the ith line and the jth column
 	@param i, the line to skip
 	@param j, the colmun to skip

 	@return the cofactor
	*/
	float getCofactor(int i, int j);

	/*
	Find the max in a column
 	@param j, the colmun

 	@return max of the jth column 
	*/
	int findColumnMax(int j_col);

	/*
	Swap two lines in a Matrix
 	@param i1, the first line number
  	@param i2, the second line number
	*/
	void swapLines(int i1, int i2);

	/*
	Multiply all the coeff in a line by a scalar
 	@param i, the line number
  	@param x, the scalar
	*/
	void multiplyLineByScalar(int i, float x);

	/*
	Compare two float according to a threshold
 	@param A, the first float
   	@param B, the second float
     	@param epsilon, the threshold
	*/
	void addLineMultipleToTargetLine(int i_target, int i_other, float coeff);

};
