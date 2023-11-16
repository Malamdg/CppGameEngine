#include "Matrix3.h"


// Private

void Matrix3::updateDet() 
{
	m_det = m_coefficients[0][0] * (m_coefficients[1][1] * m_coefficients[2][2] - m_coefficients[2][1] * m_coefficients[1][2]) 
		- m_coefficients[1][0] * (m_coefficients[0][1] * m_coefficients[2][2] - m_coefficients[2][1] * m_coefficients[0][2])
		+ m_coefficients[2][0] * (m_coefficients[0][1] * m_coefficients[1][2] - m_coefficients[1][1] * m_coefficients[0][2])
	;
}


// Public
Matrix3::Matrix3(float coefficients[3][3])
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = coefficients[i][j];
		}
	}

	updateDet();
}

Matrix3::Matrix3(const float coefficients[3][3])
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = coefficients[i][j];
		}
	}

	updateDet();
}

Matrix3::Matrix3(Vector3D column1, Vector3D column2, Vector3D column3) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			switch (i) {
			case 1:
				m_coefficients[i][j] = column2[j];
				break;
			case 2:
				m_coefficients[i][j] = column3[j];
				break;
			default:
				m_coefficients[i][j] = column1[j];
				break;
			}
		}
	}

	updateDet();
}

Matrix3::~Matrix3() {}

Matrix3 Matrix3::identity()
{
	Matrix3 matrix = Matrix3::zeros();
	for (int i = 0; i < Matrix3::m_size; i++) {
		matrix[i][i] = 1.f;
	}

	return matrix;
}

Matrix3 Matrix3::zeros()
{
	return Matrix3();
}

float Matrix3::det()
{
	return m_det;
}

void Matrix3::invert() {
	if (m_det == 0.f) {
		throw std::out_of_range("Non invertible matrix, det = 0 !");
	}

	// Augmented matrix 
	Matrix3 A = Matrix3(m_coefficients);
	Matrix3 I = Matrix3::identity();

	// Inversion stocked in var
	int permutIndex;
	float coeff;
	Matrix3 swapLinesMatrix, sumLinesMatrix;

	// Gaussian elimination
	for (int i = 0; i < m_size; i++) {
		// Set the value for the current permutation index
		permutIndex = (i + 1) % 3;
		// Setup the matrix to put 0 on i-th column 
		sumLinesMatrix = Matrix3::identity();
		
		while(A[i][i] == 0.f && i != m_size - 1) {
			// Will break algorithm if we do so
			if (permutIndex < i) {
				break;
			}

			// Setup permutation matrix to swap lines with product
			swapLinesMatrix = Matrix3::identity();
			swapLinesMatrix[i][i] = 0.f;
			swapLinesMatrix[i][permutIndex] = 1.f;
			swapLinesMatrix[permutIndex][permutIndex] = 0.f;
			swapLinesMatrix[permutIndex][i] = 1.f;
			
			// Swap lines
			A *= swapLinesMatrix;
			I *= swapLinesMatrix;

			permutIndex = (permutIndex + 1) % 3;
		}

		// Store the current diagonal coeff value, is non null by definition
		coeff = A[i][i];

		// Get 1 on current line's diagonal coefficient
		for (int j = i; j < m_size; j++) {
			A[i][j] *= 1 / coeff; // divide all line by coefficient
		}

		// Build the matrix to put the 0 on the i-th column except for the diagonal
		for (int k = 0; k < m_size; k++) {
			if (k == i) {
				continue;
			}

			sumLinesMatrix[k][i] = -1 / A[k][k];
		}

		// Apply the line operation
		A *= sumLinesMatrix;
		I *= sumLinesMatrix;
	}

	//apply inversion on this
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = I[i][j];
		}
	}
}

Matrix3 Matrix3::inverse() {
	Matrix3 inv = Matrix3(m_coefficients);
	inv.invert();
	
	return inv;
}

void Matrix3::transpose() {
	Matrix3 aRef = Matrix3(m_coefficients);
	for (int i = 0; i < m_size; i++) {
		for (int j = i + 1; j < m_size; j++) {
			m_coefficients[i][j] = aRef[j][i];
			m_coefficients[j][i] = aRef[i][j];
		}
	}
}

Matrix3 Matrix3::transposedMatrix() {
	Matrix3 transposed = Matrix3(m_coefficients);
	transposed.transpose();
	
	return transposed;
}

Matrix3& Matrix3::operator+(const Matrix3& matrix) const
{
	Matrix3 sumResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			sumResult[i][j] = m_coefficients[i][j] + matrix[i][j];
		}
	}

	return sumResult;
}

Matrix3& Matrix3::operator-(const Matrix3& matrix) const
{
	return Matrix3(m_coefficients) + (matrix * -1);
}

Matrix3& Matrix3::operator*(const Matrix3& matrix) const
{
	Matrix3 productResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			for (int k = 0; k < m_size; k++) {
				productResult[i][j] += m_coefficients[i][k]*matrix[k][j];
			}
		}
	}

	return productResult;
}

Matrix3& Matrix3::operator*(const float& lambda) const 
{
	Matrix3 productResult = Matrix3();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			productResult[i][j] = lambda * m_coefficients[i][j];
		}
	}

	return productResult;
}

Vector3D& Matrix3::operator*(const Vector3D& v) const
{
	Matrix3 prod = Matrix3(m_coefficients) * Matrix3(v);

	return Vector3D (
		prod[0][0], 
		prod[1][0], 
		prod[2][0]		
	);
}

void Matrix3::operator+=(const Matrix3& matrix) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] += matrix[i][j];
		}
	}
}

void Matrix3::operator-=(const Matrix3& matrix) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] -= matrix[i][j];
		}
	}
}

void Matrix3::operator*=(const Matrix3& matrix) 
{
	Matrix3 prod = Matrix3(m_coefficients) * matrix;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = prod[i][j];
		}
	}
}

void Matrix3::operator*=(const float& lambda) 
{
	Matrix3 prod = Matrix3(m_coefficients) * lambda;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = prod[i][j];
		}
	}
}

bool Matrix3::operator==(const Matrix3& matrix) 
{
	bool isEqual = true;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			isEqual = (m_coefficients[i][j] == matrix[i][j]);
			if (!isEqual) {
				return isEqual;
			}
		}
	}
	return isEqual;
}

float* Matrix3::operator[](int i)
{
	if (i >= 0 && i < m_size) {
		return m_coefficients[i];
	}
	else {
		throw std::out_of_range("Bad idx passed to operator[]");
	}
}

const float* Matrix3::operator[](int i) const
{
	if (i >= 0 && i < m_size) {
		return m_coefficients[i];
	}
	else {
		throw std::out_of_range("Bad idx passed to operator[]");
	}
}
