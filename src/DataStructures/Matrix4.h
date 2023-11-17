#pragma once

#include "Matrix3.h"

class Matrix4
{
public:
	static const int m_size = 4;

	Matrix4();

	Matrix4(float coeff[16]);

	~Matrix4();

	static Matrix4 Identity();

	static Matrix4 Zeros();

	float& at(int i, int j);

	const float& at(int i, int j) const;

	Matrix4& operator*(const Matrix4& m) const;

	Matrix4& operator*(const float& f) const;

	Matrix4& operator+(const Matrix4& m) const;

	Matrix4& operator-(const Matrix4& m) const;

	bool operator==(const Matrix4& m) const;

	bool operator!=(const Matrix4& m) const;

	void operator*=(const float& f);

	void operator*=(const Matrix4& m);

	void operator+=(const Matrix4& m);

	void operator-=(const Matrix4& m);

	float getDeterminant();

	void invert();

	Matrix4 Inverse();

	void transpose();

	Matrix4 Transposed();

	string toString() const;

	static bool cmpf(float A, float B, float epsilon = 10e-5);
private:
	float m_coeffs[16];

	float getCofactor(int i, int j);

	int findColumnMax(int j_col);

	void swapLines(int i1, int i2);

	void multiplyLineByScalar(int i, float x);

	void addLineMultipleToTargetLine(int i_target, int i_other, float coeff);

};