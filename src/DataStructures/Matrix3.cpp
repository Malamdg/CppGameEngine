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
	bool isEqual = true;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			isEqual = (this->at(i,j) == matrix.at(i,j));
			if (!isEqual) {
				return isEqual;
			}
		}
	}
	return isEqual;
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
	if (getDeterminant() == 0.f) {
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
	Matrix3 sumLinesMatrix;

	/// Gaussian elimination ///

	// First step
	// Make the matrix into an upper triangle
	for (int i = 0; i < m_size; i++) {
		sumLinesMatrix = Matrix3::Identity();
		
		// Store the current diagonal coeff value, is non null by definition
		coeff = A.at(i, i);

		// Get 1 on current line's diagonal coefficient
		for (int j = i; j < m_size; j++) {
			A.at(i, j) *= 1 / coeff; // divide all line by coefficient
		}

		// Build line operation
		for (int k = i + 1; k < m_size; k++) {
			sumLinesMatrix.at(k, i) = -1 / A.at(k, k);
		}

		// Apply the line operation
		A = sumLinesMatrix * A;
		I = sumLinesMatrix * I;
	}

	// Step 2
	// Make the matrix into identity
	for (int i = m_size - 1; i > 0; i--) 
	{
		Matrix3 sumLinesMatrix = Matrix3::Identity();

		// Build line operation
		for (int k = i - 1; k < m_size; k++) {
			sumLinesMatrix.at(k, i) = -1 / A.at(k, k);
		}

		// Apply the line operation
		A = sumLinesMatrix * A;
		I = sumLinesMatrix * I;
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

	float cofactor = 0;

	return direction * ((matrix2[0] * matrix2[3]) - (matrix2[1] * matrix2[2]));
}