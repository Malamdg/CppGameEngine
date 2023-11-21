#include "Matrix3.h"

// Public
Matrix3::Matrix3() 
{
	for (int i = 0; i < m_size; i++) 
	{
		for (int j = 0; j < m_size; j++)
		{
			m_coeffs[3 * i + j] = 0.f;
		}
	}
}

Matrix3::Matrix3(float coefficients[9])
{
	for (int i = 0; i < m_size * m_size; i++)
	{
		m_coeffs[i] = coefficients[i];
	}
}

Matrix3::Matrix3(Vector3D col1, Vector3D col2, Vector3D col3)
{
	for (int i = 0; i < m_size; i++)
	{
		Vector3D vector;
		switch (i) 
		{
		case 0:
			vector = col1;
			break;
		case 1:
			vector = col2;
			break;
		case 2:
			vector = col3;
			break;
		}

		for (int j = 0; j < m_size; j++)
		{
			m_coeffs[3 * i + j] = vector[j];
		}
	}
}

Matrix3& Matrix3::FromQuaternion(const Quaternion& q){
	float qx = q.getX();
	float qy = q.getY();
	float qz = q.getZ();
	float qw = q.getW();
	
	float coefficient[9];

	coefficient[0] = 1 - 2 * (qy * qy + qz * qz);
	coefficient[1] = 2 * (qx * qy + qz * qw);
	coefficient[2] = 2 * (qx * qz - qy * qw);
	coefficient[3] = 2 * (qx * qy - qz * qw);
	coefficient[4] = 1 - 2 * (qx * qx + qz * qz);
	coefficient[5] = 2 * (qy * qz + qx * qw);
	coefficient[6] = 2 * (qx * qz + qy * qw);
	coefficient[7] = 2 * (qy * qz - qz * qw);
	coefficient[8] = 1 - 2 * (qx * qx + qy * qy);

	Matrix3 mq = Matrix3(coefficient);

	return mq;
}

Matrix3::~Matrix3() {}

Matrix3 Matrix3::Identity()
{
	Matrix3 matrix = Matrix3::Zeros();
	for (int i = 0; i < Matrix3::m_size; i++) {
		matrix.at(i,i) = 1.f;
	}

	return matrix;
}

Matrix3 Matrix3::Zeros()
{
	return Matrix3();
}

Matrix3 & Matrix3::operator+(const Matrix3& matrix) const
{
	Matrix3 sumResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			sumResult.at(i,j) = this->at(i,j) + matrix.at(i,j);
		}
	}

	return sumResult;
}

Matrix3 & Matrix3::operator-(const Matrix3& matrix) const
{
	Matrix3 subResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			subResult.at(i,j) = this->at(i,j) - matrix.at(i,j);
		}
	}

	return subResult;
}

Matrix3 & Matrix3::operator*(const Matrix3& matrix) const
{
	Matrix3 productResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			for (int k = 0; k < m_size; k++) {
				productResult.at(i, j) += this->at(i,k) * matrix.at(k, j);
			}
		}
	}

	return productResult;
}

Matrix3 & Matrix3::operator*(const float& lambda) const 
{
	Matrix3 productResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			productResult.at(i,j) = lambda * this->at(i,j);
		}
	}

	return productResult;
}

Vector3D & Matrix3::operator*(const Vector3D& v) const
{
	return Vector3D (
		this->at(0,0) * v.x() + this->at(0, 1) * v.y() + this->at(0, 2) * v.z(),
		this->at(1,0) * v.x() + this->at(1, 1) * v.y() + this->at(1, 2) * v.z(),
		this->at(2,0) * v.x() + this->at(2, 1) * v.y() + this->at(2, 2) * v.z()
	);
}

bool Matrix3::operator==(const Matrix3& matrix) const
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (!cmpf(this->at(i, j), matrix.at(i, j))) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix3::operator!=(const Matrix3& matrix) const
{
	bool isDifferent = true;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			isDifferent = (this->at(i,j) != matrix.at(i,j));
			if (!isDifferent) {
				return isDifferent;
			}
		}
	}
	return isDifferent;
}

void Matrix3::operator+=(const Matrix3& matrix) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i,j) += matrix.at(i,j);
		}
	}
}

void Matrix3::operator-=(const Matrix3& matrix) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i,j) -= matrix.at(i, j);
		}
	}
}

void Matrix3::operator*=(const Matrix3& matrix) 
{
	Matrix3 prod = Matrix3(m_coeffs) * matrix;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i,j) = prod.at(i,j);
		}
	}
}

void Matrix3::operator*=(const float& lambda) 
{
	Matrix3 prod = Matrix3(m_coeffs) * lambda;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i, j) = prod.at(i,j);
		}
	}
}

float& Matrix3::at(int i, int j)
{
	if (i < 0 || i > m_size || j < 0 || j > m_size) {
		throw std::out_of_range("Bad idx passed to at()");
	}

	return m_coeffs[i*3 + j];
}

const float& Matrix3::at(int i, int j) const
{
	if (i < 0 || i >= m_size || j < 0 || j >= m_size) {
		throw std::out_of_range("Bad idx passed to at");
	}

	return m_coeffs[i * 3 + j];
}

float Matrix3::getDeterminant()
{
	float det = 0.f;
	for (int i = 0; i < m_size; i++)
	{
		det += this->at(i, 0) * getCofactor(i, 0);
	}

	return det;
}

void Matrix3::invert() {
	if (cmpf(getDeterminant(), 0.f)) {
		return;
	}

	float coeffs[9] = {};

	for (int i = 0; i < m_size*m_size; i++) {
		coeffs[i] = m_coeffs[i];
	}

	// Augmented matrix 
	Matrix3 A = Matrix3(coeffs);
	Matrix3 I = Matrix3::Identity();

	// Inversion stocked in var
	float coeff;

	/// Gaussian elimination - Gauss-Jordan algorithm ///

	int r, k;
	r = -1;

	for (int j = 0; j < m_size; j++) {
		k = A.findColumnMax(j);
		if (A.at(k, j) == 0) {
			continue;
		}

		r++;
		coeff = 1 / A.at(k, j);
		A.multiplyLineByScalar(k, coeff);
		I.multiplyLineByScalar(k, coeff);

		if (k != r) {
			A.swapLines(k, r);
			I.swapLines(k, r);
		}

		for (int i = 0; i < m_size; i++) {
			if (i == r) {
				continue;
			}
			coeff = -A.at(i,j);
			A.addLineMultipleToTargetLine(i, r, coeff);
			I.addLineMultipleToTargetLine(i, r, coeff);
		}
	}

	// Apply inversion on this
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i,j) = I.at(i,j);
		}
	}
}

Matrix3 Matrix3::Inverse() {
	Matrix3 inv = Matrix3(m_coeffs);
	inv.invert();

	return inv;
}

void Matrix3::transpose() {
	Matrix3 aRef = Matrix3(m_coeffs);
	for (int i = 0; i < m_size; i++) {
		for (int j = i + 1; j < m_size; j++) {
			this->at(i,j) = aRef.at(j, i);
			this->at(j,i) = aRef.at(i, j);
		}
	}
}

Matrix3 Matrix3::Transposed() {
	Matrix3 transposed = Matrix3(m_coeffs);
	transposed.transpose();

	return transposed;
}

string Matrix3::toString() const
{
	string buffer = "[\n";
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			buffer += to_string(m_coeffs[3 * i + j]);
			buffer += (j == m_size - 1) ? "\n" : ",";
		}
	}

	buffer += "]";
	return buffer;
}

// Private
float Matrix3::getCofactor(int i, int j)
{
	float matrix2[4] = {};
	float direction = ((i + j) % 2) == 0 ? 1 : -1;
	int idx = 0;
	for (int i_ = 0; i_ < m_size; i_++)
	{
		// Skip i-th line
		if (i == i_) {
			continue;
		}

		for (int j_ = 0; j_ < m_size; j_++)
		{
			// Skip j-th column
			if (j == j_)
			{
				continue;
			}
			matrix2[idx] = this->at(i_, j_);
			idx++;
		}
	}

	return direction * ((matrix2[0] * matrix2[3]) - (matrix2[1] * matrix2[2]));
}

int Matrix3::findColumnMax(int j_col)
{
	int i_max = j_col;

	// won't return any index over the column's one 
	for (int i = j_col; i < m_size; i++) {
		if (this->at(i, j_col) >= this->at(i_max, j_col)) {
			i_max = i;
		}
	}

	return i_max;
}

void Matrix3::swapLines(int i1, int i2) 
{
	for (int j = 0; j < m_size; j++) {
		float tmpBuffer = this->at(i1, j);
		this->at(i1, j) = this->at(i2, j);
		this->at(i2, j) = tmpBuffer;
	}
}

void Matrix3::multiplyLineByScalar(int i, float x) 
{
	for (int j = 0; j < m_size; j++) {
		this->at(i, j) *= x;
	}
}

void Matrix3::addLineMultipleToTargetLine(int i_target, int i_other, float coeff) 
{
	for (int j = 0; j < m_size; j++) {
		this->at(i_target, j) += coeff * this->at(i_other, j);
	}
}

bool Matrix3::cmpf(float A, float B, float epsilon)
{
	return (fabs(A - B) < epsilon);
}