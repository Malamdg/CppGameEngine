#include "TestsMatrix4.h"

////////// Matrix4 //////////

void TestsMatrix4::ExecuteTests()
{
	int success = 0;
	int fail = 0;

	std::cout << "--- MAtrix4 ---" << std::endl << std::endl;

	Matrix4EmtpyConstructor() ? success++ : fail++;
	Matrix4Zeros() ? success++ : fail++;
	Matrix4Id() ? success++ : fail++;
	AccessingAndModifyingMatrix4() ? success++ : fail++;
	Matrix4Addition() ? success++ : fail++;
	Matrix4Soustraction() ? success++ : fail++;
	Matrix4MatrixProduct() ? success++ : fail++;
	Matrix4FloatProduct() ? success++ : fail++;
	Matrix4DoubleFloatProduct() ? success++ : fail++;
	Matrix4Determinant() ? success++ : fail++;
	Matrix4Invert() ? success++ : fail++;
	Matrix4Inverse() ? success++ : fail++;
	Matrix4Transpose() ? success++ : fail++;
	Matrix4Transposed() ? success++ : fail++;


	std::cout << to_string(success) + " success, " + to_string(fail) + " fail" << std::endl << std::endl;
}

bool TestsMatrix4::Matrix4EmtpyConstructor()
{
	Matrix4 matrix = Matrix4();

	float coeff[16] = { 
		0, 0, 0, 0, 
		0, 0, 0, 0, 
		0, 0, 0, 0, 
		0, 0, 0, 0 
	};

	Matrix4 intendedMatrix = Matrix4(coeff);

	if (matrix == intendedMatrix)
	{
		std::cout << "Empty Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Empty Constructor : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Zeros()
{
	Matrix4 matrix = Matrix4::Zeros();

	float coeff[16] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
	};
	Matrix4 intendedMatrix = Matrix4(coeff);

	if (matrix == intendedMatrix)
	{
		std::cout << "Zeros : Success" << std::endl;
		return true;
	}

	std::cout << "Zeros : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Id()
{
	Matrix4 matrix = Matrix4::Identity();

	float coeff[16] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	};
	Matrix4 intendedMatrix = Matrix4(coeff);

	if (matrix == intendedMatrix)
	{
		std::cout << "Identity : Success" << std::endl;
		return true;
	}

	std::cout << "Identity : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::AccessingAndModifyingMatrix4()
{
	Matrix4 matrix = Matrix4();

	float coeff[16] = {
	5, 0, 0, 0,
	0, 6, 0, 0,
	0, 0, -5, 0,
	0, 0, 0, -8
	};
	Matrix4 intendedMatrix = Matrix4(coeff);

	matrix.at(0,0) = 5;
	matrix.at(1,1) = 6;
	matrix.at(2,2) = -5;
	matrix.at(3,3) = -8;

	if (matrix == intendedMatrix)
	{
		std::cout << "Access and Modification : Success" << std::endl;
		return true;
	}

	std::cout << "Access and Modification : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Addition()
{

	float coeff1[16] = {
	5, 0, 0, 0,
	0, 6, 0, 0,
	0, 0, -5, 0,
	0, 0, 0, -8
	};
	Matrix4 firstMatrix = Matrix4(coeff1);


	float coeff2[16] = {
	7, 0, 0, 0,
	0, -4, 0, 0,
	0, 0, -2.6, 0,
	0, 0, 0, 1
	};
	Matrix4 secondMatrix = Matrix4(coeff2);

	float coeff[16] = {
	12, 0, 0, 0,
	0, 2, 0, 0,
	0, 0, -7.6, 0,
	0, 0, 0, -7
	};
	Matrix4 intendedMatrix = Matrix4(coeff);

	Matrix4 sumMatrix = firstMatrix + secondMatrix;

	if (sumMatrix == intendedMatrix)
	{
		std::cout << "Addition : Success" << std::endl;
		return true;
	}

	std::cout << "Addition : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + sumMatrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Soustraction()
{
	float coeff1[16] = { 
		5, 1, 1, 1,
		2, 6, 1, 2, 
		2, 2, -5, 1,
		2, 2, -5, 2 
	};
	Matrix4 firstMatrix = Matrix4(coeff1);

	float coeff2[16] = { 
		7, 3, 3, 1, 
		-4, -4, 3, 2,
		-4, -4, -2.6, 1,
		2, 2, -5, 2
	};
	Matrix4 secondMatrix = Matrix4(coeff2);

	Matrix4 subMatrix = firstMatrix - secondMatrix;

	float coeff[16] = { 
		-2, -2, -2, 0,
		6, 10, -2, 0,
		6, 6, -2.4, 0,
		0, 0, 0, 0 
	};
	Matrix4 intendedMatrix = Matrix4(coeff);

	if (subMatrix == intendedMatrix)
	{
		std::cout << "Soustraction : Success" << std::endl;
		return true;
	}

	std::cout << "Soustraction : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + subMatrix.toString() << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + subMatrix.toString() << std::endl;
}

bool TestsMatrix4::Matrix4MatrixProduct()
{
	float coeff1[16] = {
		5, 1, 3, 1, 
		2, 6, 0, 2, 
		-4, 0.1, -5, 1,
		0, 0, 0, 1 
	};
	Matrix4 firstMatrix = Matrix4(coeff1);

	float coeff2[16] = { 
		7, 3.1, 6, 3,
		0.5, -4, -1, -1, 
		-0.5, 1, -2.6, -4, 
		0, 0, 0, 1 
	};
	Matrix4 secondMatrix = Matrix4(coeff2);

	Matrix4 productMatrix = firstMatrix * secondMatrix;

	float coeff[16] = { 
		34, 14.5, 21.2, 3, 
		17, -17.8, 6, 2, 
		-25.45, -17.8, -11.1, 8.9, 
		0, 0, 0, 1 
	};
	Matrix4 intendedMatrix = Matrix4(coeff);

	if (productMatrix == intendedMatrix)
	{
		std::cout << "Matrix x Matrix Product : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix x Matrix Product : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + productMatrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4FloatProduct()
{
	Matrix4 matrix = Matrix4::Identity();
	float f1 = 12.65;

	float coeff2[16] = {
		f1, 0, 0, 0, 
		0, f1, 0, 0,
		0, 0, f1, 0, 
		0, 0, 0, f1
	};
	Matrix4 intendedMatrix = Matrix4(coeff2);
	Matrix4 result = matrix * f1;

	if (result == intendedMatrix)
	{
		std::cout << "Matrix Product float : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix Product float : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + result.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4DoubleFloatProduct()
{
	Matrix4 matrix = Matrix4::Identity();
	
	float f1 = 12.65;
	float f2 = 16.69;

	float coeff2[16] = {
		f1 * f2, 0, 0, 0,
		0, f1 * f2, 0, 0,
		0, 0, f1 * f2, 0,
		0, 0, 0, f1 * f2
	};
	Matrix4 intendedMatrix = Matrix4(coeff2);
	Matrix4 result = matrix * (f1 * f2);

	if (result == intendedMatrix)
	{
		std::cout << "Matrix Product double float : Success" << std::endl;
		return true;
	}

	std::cout << "Matrix Product double float : Fail. " << std::endl;
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + result.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Determinant()
{
	float coeff1[16] = {
		6, 1, 3, 1,
		2, 6, 0, 2,
		1, 0, 4, 2,
		-1, 3, 1, -7
	};
	Matrix4 matrix = Matrix4(coeff1);

	float det = -1048;
	float compute_det = matrix.getDeterminant();

	if (Matrix4::cmpf(det, compute_det))
	{
		std::cout << "Determinant : Success" << std::endl;
		return true;
	}

	std::cout << "Determinant : Fail. ";
	std::cout << "Expected :" + to_string(det) << std::endl;
	std::cout << "Got : " + to_string(compute_det) << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Invert()
{
	float coeff1[16] = {
		6, 1, 3, 1,
		2, 6, 0, 2,
		1, 0, 4, 2,
		-1, 3, 1, -7
	};
	Matrix4 matrix = Matrix4(coeff1);

	float coeff2[16] = {
		0.1946564885496183206, -0.022900763358778625956, -0.14122137404580152672, -0.019083969465648854957,
		-0.047709923664122137444, 0.15267175572519083976, 0.024809160305343511478, 0.043893129770992366284,
		-0.022900763358778625957, -0.02671755725190839695, 0.25190839694656488551, 0.061068702290076335884,
		-0.051526717557251908393, 0.064885496183206106879, 0.066793893129770992326, -0.11259541984732824429
	};
	Matrix4 intendedMatrix = Matrix4(coeff2);

	matrix.invert();

	if (matrix == intendedMatrix)
	{
		std::cout << "Invert matrix : Success" << std::endl;
		return true;
	}

	std::cout << "Invert matrix : Fail. ";
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Inverse()
{
	float coeff1[16] = {
		6, 1, 3, 1,
		2, 6, 0, 2,
		1, 0, 4, 2,
		-1, 3, 1, -7 
	};
	Matrix4 matrix = Matrix4(coeff1);

	float coeff2[16] = { 
		0.1946564885496183206, -0.022900763358778625956, -0.14122137404580152672, -0.019083969465648854957, 
		-0.047709923664122137444, 0.15267175572519083976, 0.024809160305343511478, 0.043893129770992366284, 
		-0.022900763358778625957, -0.02671755725190839695, 0.25190839694656488551, 0.061068702290076335884, 
		-0.051526717557251908393, 0.064885496183206106879, 0.066793893129770992326, -0.11259541984732824429 
	};
	Matrix4 intendedMatrix = Matrix4(coeff2);

	matrix = matrix.Inverse();

	if (matrix == intendedMatrix)
	{
		std::cout << "Inversed matrix : Success" << std::endl;
		return true;
	}

	std::cout << "Inversed matrix : Fail. ";
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + matrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Transpose()
{
	float coeff1[16] = { 
		6, 1, 3, 1,
		2, 6, 0, 2,
		1, 0, 4, 2,
		-1, 3, 1, -7 
	};
	Matrix4 matrix = Matrix4(coeff1);

	float coeff2[16] = {
		6, 2, 1, -1,
		1, 6, 0, 3,
		3, 0, 4, 1,
		1, 2, 2, -7
	};
	Matrix4 intendedMatrix = Matrix4(coeff2);

	matrix.transpose();

	if (matrix == intendedMatrix)
	{
		std::cout << "Transpose : Success" << std::endl;
		return true;
	}

	std::cout << "Transpose : Fail. ";
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + intendedMatrix.toString() << std::endl;
	return false;
}

bool TestsMatrix4::Matrix4Transposed()
{
	float coeff1[16] = { 
		6, 1, 3, 1,
		2, 6, 0, 2,
		1, 0, 4, 2,
		-1, 3, 1, -7 
	};
	Matrix4 matrix = Matrix4(coeff1);

	float coeff2[16] = {
		6, 2, 1, -1,
		1, 6, 0, 3,
		3, 0, 4, 1,
		1, 2, 2, -7
	};
	Matrix4 intendedMatrix = Matrix4(coeff2);

	matrix = matrix.Transposed();

	if (matrix == intendedMatrix)
	{
		std::cout << "Transpose : Success" << std::endl;
		return true;
	}

	std::cout << "Transpose : Fail. ";
	std::cout << "Expected :" + intendedMatrix.toString() << std::endl;
	std::cout << "Got : " + intendedMatrix.toString() << std::endl;
	return false;
}