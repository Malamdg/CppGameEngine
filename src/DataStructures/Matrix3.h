#pragma once

#include "Vector3D.h"

class Matrix3 
{
public:
	static const int m_size = 3;

	Matrix3();
	
	Matrix3(float coeff[9]);

	Matrix3(Vector3D col1, Vector3D col2, Vector3D col3);
	
	~Matrix3();

	static Matrix3 Identity();

	static Matrix3 Zeros();

	float& at(int i, int j);

	const float& at(int i, int j) const;

	Matrix3 & operator*(const Matrix3& m) const;

	Vector3D & operator*(const Vector3D& v) const;

	Matrix3 & operator*(const float& f) const;

	Matrix3 & operator+(const Matrix3& m) const;

	Matrix3 & operator-(const Matrix3& m) const;

	bool operator==(const Matrix3& m) const;
	
	bool operator!=(const Matrix3& m) const;

	void operator*=(const float& f);

	void operator*=(const Matrix3& m);

	void operator+=(const Matrix3& m);

	void operator-=(const Matrix3& m);

	float getDeterminant();

	void invert();

	Matrix3 Inverse();

	void transpose();

	Matrix3 Transposed();
	
	string toString() const;

private:
	float m_coeffs[9];

	float getCofactor(int i, int j);

	int findColumnMax(int j_col);

	void swapLines(int i1, int i2);

	void multiplyLineByScalar(int i, float x);

	void addLineMultipleToTargetLine(int i_target, int i_other, float coeff);

	static bool cmpf(float A, float B, float epsilon = 10e-5);
};