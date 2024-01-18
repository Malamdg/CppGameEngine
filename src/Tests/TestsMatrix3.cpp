#include "TestsMAtrix3.h"

////////// Matrix3 //////////

void TestsMatrix3::ExecuteTests()
{
	int success = 0;
	int fail = 0;

	std::cout << "--- Matrix3 ---" << std::endl << std::endl;

	Matrix3EmtpyConstructor() ? success++ : fail++;
	Matrix3VectorConstructor() ? success++ : fail++;
	Matrix3Zeros() ? success++ : fail++;
	Matrix3Id() ? success++ : fail++;
	AccessingAndModifyingMatrix3() ? success++ : fail++;
	Matrix3Addition() ? success++ : fail++;
	Matrix3Soustraction() ? success++ : fail++;
	Matrix3MatrixProduct() ? success++ : fail++;
	Matrix3Vector3DProduct() ? success++ : fail++;
	Matrix3FloatProduct() ? success++ : fail++;
	Matrix3DoubleFloatProduct() ? success++ : fail++;
	Matrix3Determinant() ? success++ : fail++;
	Matrix3Invert() ? success++ : fail++;
	Matrix3Inverse() ? success++ : fail++;
	Matrix3Transpose() ? success++ : fail++;
	Matrix3Transposed() ? success++ : fail++;

	std::cout << to_string(success) + " success, " + to_string(fail) + " fail" << std::endl << std::endl;
}

bool TestsMatrix3::Matrix3EmtpyConstructor()
{
	Matrix3 matrix = Matrix3();
	float coeff[9] = { 
		0,0,0, 
		0,0,0, 
		0,0,0 
	};

	Matrix3 intendedMatrix = Matrix3(coeff);

	if (matrix == intendedMatrix)
	{
		std::cout << "Empty Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Empty Constructor : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3VectorConstructor()
{
	Vector3D vec1 = Vector3D(1, 1, 1);
	Vector3D vec2 = Vector3D(-1, 1, -1);
	Vector3D vec3 = Vector3D(0.5, 1, 0.5);
	Matrix3 matrix = Matrix3(vec1, vec2, vec3);
	float coeffs[9] = {
		1, 1, 1, 
		-1, 1, -1,
		0.5, 1, 0.5
	};
	Matrix3 intendedMatrix = Matrix3(coeffs);

	if (matrix == intendedMatrix)
	{
		std::cout << "Vector Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Vector Constructor : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Zeros()
{
	Matrix3 matrix = matrix.Zeros();
	
	float coeffs[9] = {
		0,0,0,
		0,0,0,
		0,0,0
	};

	Matrix3 intendedMatrix = Matrix3(coeffs);

	if (matrix == intendedMatrix)
	{
		std::cout << "Zeros : Success" << std::endl;
		return true;
	}

	std::cout << "Zeros : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Id()
{
	Matrix3 matrix = Matrix3::Identity();
	float coeffs[9] = {
		1,0,0,
		0,1,0,
		0,0,1
	};
	Matrix3 intendedMatrix = Matrix3(coeffs);

	if (matrix == intendedMatrix)
	{
		std::cout << "Identity : Success" << std::endl;
		return true;
	}

	std::cout << "Identity : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::AccessingAndModifyingMatrix3()
{
	Matrix3 matrix = Matrix3();
	float coeff[9] = { 
		5.f,0,0,
		0, 6.f,0,
		0,0,-5.f
	};

	Matrix3 intendedMatrix = Matrix3(coeff);

	matrix.at(0,0) = 5.f;
	matrix.at(1,1) = 6.f;
	matrix.at(2,2) = -5.f;

	if (matrix == intendedMatrix)
	{
		std::cout << "Access and Modification : Success" << std::endl;
		return true;
	}

	std::cout << "Access and Modification : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3MatrixProduct()
{
	float coeff1[9] =
	{
		5, 1, 3,
		2, 6, 0,
		-4, 0.1, -5
	};
	Matrix3 firstMatrix = Matrix3(coeff1);

	float coeff2[9] =
	{
		7, 3.1, 6,
		0.5, -4, -1,
		-0.5, 1, -2.6
	};
	Matrix3 secondMatrix = Matrix3(coeff2);

	Matrix3 productMatrix = firstMatrix * secondMatrix;

	float coeff3[9] =
	{
		34, 14.5, 21.2,
		17, -17.8, 6,
		-25.45, -17.8, -11.1
	};
	Matrix3 intendedMatrix = Matrix3(coeff3);

	if (productMatrix == intendedMatrix)
	{
		std::cout << "Matrix x Matrix Product : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix x Matrix Product : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + productMatrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Vector3DProduct()
{
	float coeff1[9] =
	{
		1, 0, 0,
		0, 2, 0,
		0, 0, 3
	};
	Matrix3 firstMatrix = Matrix3(coeff1);

	Vector3D v = Vector3D(4, 5, 6);

	Vector3D productResult = firstMatrix * v;

	Vector3D intendedVector = Vector3D(4, 10, 18);

	if (productResult == intendedVector)
	{
		std::cout << "Matrix x Vector Product : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix x Vector Product : Fail. " << std::endl;
	std::cout << "Expected :" + intendedVector.toString() << std::endl;
	std::cout << "Got :" + productResult.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3FloatProduct()
{
	float coeffs[9] = {
		1,0,0,
		0,1,0,
		0,0,1
	};

	Matrix3 matrix = Matrix3(coeffs);
	float f1 = 12.65;

	float coeffs2[9] = {
		f1, 0, 0,
		0, f1, 0,
		0, 0, f1
	};

	Matrix3 intendedMatrix = Matrix3(coeffs2);
	Matrix3 result = matrix * f1;

	if (result == intendedMatrix)
	{
		std::cout << "Matrix Product float : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix Product float : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + result.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3DoubleFloatProduct()
{
	float coeffs[9] = {
		1,0,0,
		0,1,0,
		0,0,1
	};

	Matrix3 matrix = Matrix3(coeffs);
	float f1 = 12.65;
	float f2 = 16.69;

	float coeffs2[9] = {
		f1 * f2, 0, 0,
		0, f1 * f2, 0,
		0, 0, f1 * f2
	};

	Matrix3 intendedMatrix = Matrix3(coeffs2);
	Matrix3 result = matrix * (f1 * f2);

	if (result == intendedMatrix)
	{
		std::cout << "Matrix Product float by float : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix Product float by float : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + result.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Addition()
{
	float coeff1[9] = {
		5, 0, 0,
		0, 6, 0,
		0, 0, -5
	};

	Matrix3 firstMatrix = Matrix3(coeff1);

	float coeff2[9] = { 
		7, 0, 0, 
		0, -4, 0, 
		0, 0, -2.6
	};
	Matrix3 secondMatrix = Matrix3(coeff2);

	Matrix3 sumMatrix = firstMatrix + secondMatrix;

	float coeff3[9] = {
		12, 0, 0,
		0, 2, 0,
		0, 0, -7.6
	};

	Matrix3 intendedMatrix = Matrix3(coeff3);

	if (sumMatrix == intendedMatrix)
	{
		std::cout << "Addition : Success" << std::endl;
		return true;
	}

	std::cout << "Addition : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + sumMatrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Soustraction()
{

	float coeff1[9] = 
	{ 
		5, 1, 1,
		2, 6, 1,
		2, 2, -5 
	};

	Matrix3 firstMatrix = Matrix3(coeff1);

	float coeff2[9] = 
	{ 
		7, 3, 3 , 
		-4, -4, 3, 
		-4, -4, -2.6 
	};
	Matrix3 secondMatrix = Matrix3(coeff2);

	Matrix3 subMatrix = firstMatrix - secondMatrix;

	float coeff3[9] = 
	{ 
		-2, -2, -2, 
		6, 10, -2, 
		6, 6, -2.4 
	};
	Matrix3 intendedMatrix = Matrix3(coeff3);

	if (subMatrix == intendedMatrix)
	{
		std::cout << "Subtract : Success" << std::endl;
		return true;
	}

	std::cout << "Subtract : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + subMatrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Determinant()
{
	float coeff1[9] = {
		5, 1, 3,
		2, 6, 0,
		-4, 0.1, -5
	};
	Matrix3 matrix = Matrix3(coeff1);

	float det = -67.4;
	float compute_det = matrix.getDeterminant();

	if (abs(det - compute_det) < 10e-5)
	{
		std::cout << "Determinant : Success" << std::endl;
		std::cout << "Expected :" + to_string(det) << std::endl;
		std::cout << "Got :" + to_string(compute_det) << std::endl;
		std::cout << "Delta :" + to_string(abs(det - compute_det)) << std::endl;
		return true;
	}

	std::cout << "Determinant : Fail. " << std::endl;
	std::cout << "Expected :" + to_string(det) << std::endl;
	std::cout << "Got :" + to_string(compute_det) << std::endl;
	std::cout << "Delta :" + to_string(abs(det - compute_det)) << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Invert()
{
	float coeff1[9] =
	{
		5, 1, 3,
		2, 6, 0,
		-4, 0.1, -5
	};
	Matrix3 matrix = Matrix3(coeff1);

	float coeff2[9] =
	{
		0.44510385756676557863, -0.07863501483679525222, 0.26706231454005934718,
		-0.14836795252225519287, 0.19287833827893175073, -0.089020771513353115725,
		-0.35905044510385756677, 0.06676557863501483679, -0.41543026706231454006
	};
	Matrix3 intendedMatrix = Matrix3(coeff2);
	
	matrix.invert();

	if (matrix == intendedMatrix)
	{
		std::cout << "Invert : Success" << std::endl;
		return true;
	}

	std::cout << "Invert : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Inverse()
{
	float coeff1[9] = 
	{ 
		5, 1, 3, 
		2, 6, 0, 
		-4, 0.1, -5
	};
	Matrix3 matrix = Matrix3(coeff1);

	float coeff2[9] = 
	{ 
		0.44510385756676557863, -0.07863501483679525222, 0.26706231454005934718, 
		-0.14836795252225519287, 0.19287833827893175073, -0.089020771513353115725,
		-0.35905044510385756677, 0.06676557863501483679, -0.41543026706231454006 
	};
	Matrix3 intendedMatrix = Matrix3(coeff2);

	matrix = matrix.Inverse();

	if (matrix == intendedMatrix)
	{
		std::cout << "Inversed matrix : Success" << std::endl;
		return true;
	}

	std::cout << "Inversed matrix: Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Transpose()
{
	float coeff1[9] = 
	{ 
		5, 1, 3, 
		2, 6, 0, 
		-4, 0.1, -5 
	};
	Matrix3 matrix = Matrix3(coeff1);

	float coeff2[9] = 
	{ 
		5, 2, -4, 
		1, 6, 0.1, 
		3, 0, -5 
	};
	Matrix3 intendedMatrix = Matrix3(coeff2);

	matrix.transpose();

	if (matrix == intendedMatrix)
	{
		std::cout << "Transpose : Success" << std::endl;
		return true;
	}

	std::cout << "Transpose : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix3::Matrix3Transposed()
{
	float coeff1[9] = 
	{ 
		5, 1, 3, 
		2, 6, 0, 
		-4, 0.1, -5 
	};
	Matrix3 matrix = Matrix3(coeff1);

	float coeff2[9] = 
	{ 
		5, 2, -4, 
		1, 6, 0.1, 
		3, 0, -5 
	};
	Matrix3 intendedMatrix = Matrix3(coeff2);

	Matrix3 transposedMatrix = matrix.Transposed();

	if (transposedMatrix == intendedMatrix)
	{
		std::cout << "Transposed matrix : Success" << std::endl;
		return true;
	}

	std::cout << "Transposed matrix : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got :" + transposedMatrix.toString() << std::endl;
	return false;
}