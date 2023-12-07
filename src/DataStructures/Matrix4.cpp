#include "Matrix4.h"

// Public
Matrix4::Matrix4()
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			m_coeffs[4 * i + j] = 0.f;
		}
	}
}

Matrix4::Matrix4(float coefficients[16])
{
	for (int i = 0; i < m_size * m_size; i++)
	{
		m_coeffs[i] = coefficients[i];
	}
}

Matrix4::~Matrix4() {}

Matrix4 Matrix4::Identity()
{
	Matrix4 matrix = Matrix4::Zeros();
	for (int i = 0; i < Matrix4::m_size; i++) {
		matrix.at(i, i) = 1.f;
	}

	return matrix;
}

Matrix4 Matrix4::Zeros()
{
	return Matrix4();
}

Matrix4& Matrix4::operator+(const Matrix4& matrix) const
{
	Matrix4 sumResult = Matrix4();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			sumResult.at(i, j) = this->at(i, j) + matrix.at(i, j);
		}
	}

	return sumResult;
}

Matrix4& Matrix4::operator-(const Matrix4& matrix) const
{
	Matrix4 subResult = Matrix4();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			subResult.at(i, j) = this->at(i, j) - matrix.at(i, j);
		}
	}

	return subResult;
}

Matrix4& Matrix4::operator*(const Matrix4& matrix) const
{
	Matrix4 productResult = Matrix4();
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			for (int k = 0; k < m_size; k++) {
				productResult.at(i, j) += this->at(i, k) * matrix.at(k, j);
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
			productResult.at(i, j) = lambda * this->at(i, j);
		}
	}

	return productResult;
}


Vector3D& Matrix4::operator*(const Vector3D& v) const
{
	return Vector3D
	(
		this->at(0, 0) * v[0] + this->at(0, 1) * v[1] + this->at(0, 2) * v[2] + this->at(0, 3) * v[3],
		this->at(1, 0) * v[0] + this->at(1, 1) * v[1] + this->at(1, 2) * v[2] + this->at(1, 3) * v[3],
		this->at(2, 0) * v[0] + this->at(2, 1) * v[1] + this->at(2, 2) * v[2] + this->at(2, 3) * v[3],
		this->at(3, 0) * v[0] + this->at(3, 1) * v[1] + this->at(3, 2) * v[2] + this->at(3, 3) * v[3]
	);
}

bool Matrix4::operator==(const Matrix4& matrix) const
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

bool Matrix4::operator!=(const Matrix4& matrix) const
{
	bool isDifferent = true;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			isDifferent = (this->at(i, j) != matrix.at(i, j));
			if (!isDifferent) {
				return isDifferent;
			}
		}
	}
	return isDifferent;
}

void Matrix4::operator+=(const Matrix4& matrix)
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i, j) += matrix.at(i, j);
		}
	}
}

void Matrix4::operator-=(const Matrix4& matrix)
{
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i, j) -= matrix.at(i, j);
		}
	}
}

void Matrix4::operator*=(const Matrix4& matrix)
{
	Matrix4 prod = Matrix4(m_coeffs) * matrix;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i, j) = prod.at(i, j);
		}
	}
}

void Matrix4::operator*=(const float& lambda)
{
	Matrix4 prod = Matrix4(m_coeffs) * lambda;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i, j) = prod.at(i, j);
		}
	}
}

float& Matrix4::at(int i, int j)
{
	if (i < 0 || i > m_size || j < 0 || j > m_size) {
		throw std::out_of_range("Bad idx passed to at()");
	}

	return m_coeffs[i * 4 + j];
}

const float& Matrix4::at(int i, int j) const
{
	if (i < 0 || i >= m_size || j < 0 || j >= m_size) {
		throw std::out_of_range("Bad idx passed to at");
	}

	return m_coeffs[i * 4 + j];
}

float Matrix4::getDeterminant()
{
	float det = 0.f;
	for (int i = 0; i < m_size; i++)
	{
		det += this->at(i, 0) * getCofactor(i, 0);
	}

	return det;
}

void Matrix4::invert() {
	if (getDeterminant() == 0.f) {
		return;
	}

	float coeffs[16] = {};

	for (int i = 0; i < m_size * m_size; i++) {
		coeffs[i] = m_coeffs[i];
	}

	// Augmented matrix 
	Matrix4 A = Matrix4(coeffs);
	Matrix4 I = Matrix4::Identity();

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
			coeff = -A.at(i, j);
			A.addLineMultipleToTargetLine(i, r, coeff);
			I.addLineMultipleToTargetLine(i, r, coeff);
		}
	}

	// Apply inversion on this
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			this->at(i, j) = I.at(i, j);
		}
	}
}

Matrix4 Matrix4::Inverse() {
	Matrix4 inv = Matrix4(m_coeffs);
	inv.invert();

	return inv;
}

void Matrix4::transpose() {
	Matrix4 aRef = Matrix4(m_coeffs);
	for (int i = 0; i < m_size; i++) {
		for (int j = i + 1; j < m_size; j++) {
			this->at(i, j) = aRef.at(j, i);
			this->at(j, i) = aRef.at(i, j);
		}
	}
}

Matrix4 Matrix4::Transposed() {
	Matrix4 transposed = Matrix4(m_coeffs);
	transposed.transpose();

	return transposed;
}

Matrix4 Matrix4::augment(Matrix3 m3, Vector3D rightmostColumn)
{
	Matrix4 augmentedMatrix = Matrix4();

	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			augmentedMatrix.at(i, j) = m3.at(i, j);
		}
	}

	augmentedMatrix.at(0, 3) = rightmostColumn.x();
	augmentedMatrix.at(1, 3) = rightmostColumn.y();
	augmentedMatrix.at(2, 3) = rightmostColumn.z();
	augmentedMatrix.at(3, 3) = rightmostColumn.w();

	return augmentedMatrix;
}

string Matrix4::toString() const
{
	string buffer = "[\n";
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			buffer += to_string(m_coeffs[4 * i + j]);
			buffer += (j == m_size - 1) ? "\n" : ",";
		}
	}

	buffer += "]";
	return buffer;
}

// Private
float Matrix4::getCofactor(int i, int j)
{
	float coeffs[9] = {};
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
			coeffs[idx] = this->at(i_, j_);
			idx++;
		}
	}

	Matrix3 comatrix = Matrix3(coeffs);

	return direction * comatrix.getDeterminant();
}

int Matrix4::findColumnMax(int j_col)
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

void Matrix4::swapLines(int i1, int i2)
{
	for (int j = 0; j < m_size; j++) {
		float tmpBuffer = this->at(i1, j);
		this->at(i1, j) = this->at(i2, j);
		this->at(i2, j) = tmpBuffer;
	}
}

void Matrix4::multiplyLineByScalar(int i, float x)
{
	for (int j = 0; j < m_size; j++) {
		this->at(i, j) *= x;
	}
}

void Matrix4::addLineMultipleToTargetLine(int i_target, int i_other, float coeff)
{
	for (int j = 0; j < m_size; j++) {
		this->at(i_target, j) += coeff * this->at(i_other, j);
	}
}

bool Matrix4::cmpf(float A, float B, float epsilon)
{
	return (fabs(A - B) < epsilon);
}