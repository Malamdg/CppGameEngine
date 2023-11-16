#include "Matrix4.h"


// Private

void Matrix4::updateDet() 
{
	m_det = m_coefficients[0][0] * (m_coefficients[1][1] * m_coefficients[2][2] - m_coefficients[2][1] * m_coefficients[1][2]) 
		- m_coefficients[1][0] * (m_coefficients[0][1] * m_coefficients[2][2] - m_coefficients[2][1] * m_coefficients[0][2])
		+ m_coefficients[2][0] * (m_coefficients[0][1] * m_coefficients[1][2] - m_coefficients[1][1] * m_coefficients[0][2])
	; // METTRE A JOUR
}


// Public
Matrix4::Matrix4(float coefficients[4][4])
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = coefficients[i][j];
		}
	}

	updateDet();
}

Matrix4::Matrix4(const float coefficients[4][4])
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = coefficients[i][j];
		}
	}

	updateDet();
}

Matrix4::Matrix4(Vector3D column1, Vector3D column2, Vector3D column3, Vector3D column4)
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
			case 3:
				m_coefficients[i][j] = column4[j];
				break;
			default:
				m_coefficients[i][j] = column1[j];
				break;
			}
		}
	}

	updateDet();
}

Matrix4::~Matrix4() {}

Matrix4 Matrix4::identity()
{
	Matrix4 matrix = Matrix4::zeros();
	for (int i = 0; i < Matrix4::m_size; i++) {
		matrix[i][i] = 1.f;
	}

	return matrix;
}

Matrix4 Matrix4::zeros()
{
	return Matrix4();
}

float Matrix4::det()
{
	return m_det;
}


// METTRE A JOUR
void Matrix4::invert() {
	if (m_det == 0.f) {
		throw std::out_of_range("Non invertible matrix, det = 0 !");
	}

	// Augmented matrix 
	Matrix4 A = Matrix4(m_coefficients);
	Matrix4 I = Matrix4::identity();

	// Inversion stocked in var
	int permutIndex;
	float coeff;
	Matrix4 swapLinesMatrix, sumLinesMatrix;

	// Gaussian elimination
	for (int i = 0; i < m_size; i++) {
		// Set the value for the current permutation index
		permutIndex = (i + 1) % 3;
		// Setup the matrix to put 0 on i-th column 
		sumLinesMatrix = Matrix4::identity();
		
		while(A[i][i] == 0.f && i != m_size - 1) {
			// Will break algorithm if we do so
			if (permutIndex < i) {
				break;
			}

			// Setup permutation matrix to swap lines with product
			swapLinesMatrix = Matrix4::identity();
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

Matrix4 Matrix4::inverse() {
	Matrix4 inv = Matrix4(m_coefficients);
	inv.invert();
	
	return inv;
}

void Matrix4::transpose() {
	Matrix4 aRef = Matrix4(m_coefficients);
	for (int i = 0; i < m_size; i++) {
		for (int j = i + 1; j < m_size; j++) {
			m_coefficients[i][j] = aRef[j][i];
			m_coefficients[j][i] = aRef[i][j];
		}
	}
}

Matrix4 Matrix4::transposedMatrix() {
	Matrix4 transposed = Matrix4(m_coefficients);
	transposed.transpose();
	
	return transposed;
}

Matrix4& Matrix4::operator+(const Matrix4& matrix) const
{
	Matrix4 sumResult = Matrix4();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			sumResult[i][j] = m_coefficients[i][j] + matrix[i][j];
		}
	}

	return sumResult;
}

Matrix4& Matrix4::operator-(const Matrix4& matrix) const
{
	return Matrix4(m_coefficients) + (matrix * -1);
}

Matrix4& Matrix4::operator*(const Matrix4& matrix) const
{
	Matrix4 productResult = Matrix4();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			for (int k = 0; k < m_size; k++) {
				productResult[i][j] += m_coefficients[i][k]*matrix[k][j];
			}
		}
	}

	return productResult;
}

Matrix4& Matrix4::operator*(const float& lambda) const 
{
	Matrix4 productResult = Matrix4();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			productResult[i][j] = lambda * m_coefficients[i][j];
		}
	}

	return productResult;
}

void Matrix4::operator+=(const Matrix4& matrix) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] += matrix[i][j];
		}
	}
}

void Matrix4::operator-=(const Matrix4& matrix) 
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] -= matrix[i][j];
		}
	}
}

void Matrix4::operator*=(const Matrix4& matrix) 
{
	Matrix4 prod = Matrix4(m_coefficients) * matrix;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = prod[i][j];
		}
	}
}

void Matrix4::operator*=(const float& lambda) 
{
	Matrix4 prod = Matrix4(m_coefficients) * lambda;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			m_coefficients[i][j] = prod[i][j];
		}
	}
}

bool Matrix4::operator==(const Matrix4& matrix) 
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

float* Matrix4::operator[](int i)
{
	switch (i)
	{
	case 0: return m_coefficients[i];
	case 1: return m_coefficients[i];
	case 2: return m_coefficients[i];
	case 3: return m_coefficients[i];
	default: throw std::out_of_range("Bad idx passed to at()");
	}
}

const float* Matrix4::operator[](int i) const 
{
	switch (i)
	{
	case 0: return m_coefficients[i];
	case 1: return m_coefficients[i];
	case 2: return m_coefficients[i];
	case 3: return m_coefficients[i];
	default: throw std::out_of_range("Bad idx passed to at()");
	}
};