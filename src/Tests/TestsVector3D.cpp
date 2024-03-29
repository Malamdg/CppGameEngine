#include "TestsVector3D.h"

void TestsVector3D::ExecuteTests()
{
	int success = 0;
	int fail = 0;

	std::cout << "--- Vector3D ---" << std::endl << std::endl;

	Vector3DEmtpyConstructor() ? success++ : fail++;
	AccessingAndModifyingVector3D() ? success++ : fail++;
	Vector3DAddition() ? success++ : fail++;
	Vector3DSoustraction() ? success++ : fail++;
	Vector3DScalarProduct() ? success++ : fail++;
	Vector3DNorm() ? success++ : fail++;
	Vector3DNorm2() ? success++ : fail++;
	Vector3DNormalization() ? success++ : fail++;
	Vector3DVectorProduct() ? success++ : fail++;
	Vector3Dfloatfloat() ? success++ : fail++;

	std::cout << to_string(success) + " success, " + to_string(fail) + " fail" << std::endl << std::endl;
}

bool TestsVector3D::Vector3DEmtpyConstructor()
{
	Vector3D vector = Vector3D();
	Vector3D intendedVector = Vector3D(0, 0, 0);

	if (vector == intendedVector)
	{
		std::cout << "Empty Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Empty Constructor : Fail. ";
	std::cout << "Was expecting (0, 0, 0), got " + vector.toString() << std::endl;
	return false;
}

bool TestsVector3D::AccessingAndModifyingVector3D()
{
	Vector3D vector = Vector3D();
	Vector3D intendedVector = Vector3D(5, 6, -5);

	vector[0] = 5;
	vector[1] = 6;
	vector[2] = -5;

	if (vector == intendedVector)
	{
		std::cout << "Access and Modification : Success" << std::endl;
		return true;
	}

	std::cout << "Access and Modification : Fail. ";
	std::cout << "Was expecting (5, 6, -5), got " + vector.toString() << std::endl;
	return false;
}

bool TestsVector3D::Vector3DAddition()
{
	Vector3D firstVector = Vector3D(5, 6, -5);
	Vector3D secondVector = Vector3D(7, -4, -2.6);

	Vector3D sumVector = firstVector + secondVector;
	Vector3D intendedVector = Vector3D(12, 2, -7.6);

	if (sumVector == intendedVector)
	{
		std::cout << "Addition : Success" << std::endl;
		return true;
	}

	std::cout << "Addition : Fail. ";
	std::cout << "Was expecting (12, 2, -7.6), got " + sumVector.toString() << std::endl;
	return false;
}

bool TestsVector3D::Vector3DSoustraction()
{
	Vector3D firstVector = Vector3D(5, 6, -5);
	Vector3D secondVector = Vector3D(7, -4, -2.6);

	Vector3D subVector = firstVector - secondVector;
	Vector3D intendedVector = Vector3D(-2, 10, -2.4);

	if (subVector == intendedVector)
	{
		std::cout << "Soustraction : Success" << std::endl;
		return true;
	}

	std::cout << "Soustraction : Fail. ";
	std::cout << "Was expecting (-2, 10, -2.4), got " + subVector.toString() << std::endl;
	return false;
}

bool TestsVector3D::Vector3DScalarProduct()
{
	Vector3D firstVector = Vector3D(5, 6, -5);
	Vector3D secondVector = Vector3D(7, -4, -2.6);

	float scalarProduct = firstVector * secondVector;
	float intendedResult = 24;

	if (scalarProduct == intendedResult)
	{
		std::cout << "Scalar Product : Success" << std::endl;
		return true;
	}

	std::cout << "Scalar Product : Fail. ";
	std::cout << "Was expecting 24, got " + to_string(scalarProduct) << std::endl;
	return false;
}

bool TestsVector3D::Vector3DNorm()
{
	Vector3D vector = Vector3D(5, 6, -5);

	float norm = vector.Norm();
	float intendedNorm = sqrt(86);

	if (norm == intendedNorm)
	{
		std::cout << "Norm : Success" << std::endl;
		return true;
	}

	std::cout << "Norm : Fail. ";
	std::cout << "Was expecting " + to_string(intendedNorm) + ", got " + to_string(norm) << std::endl;
	return false;
}

bool TestsVector3D::Vector3DNorm2()
{
	Vector3D vector = Vector3D(5, 6, -5);

	float norm = vector.Norm2();
	float intendedNorm = 86;

	if (norm == intendedNorm)
	{
		std::cout << "Norm2 : Success" << std::endl;
		return true;
	}

	std::cout << "Norm2 : Fail. ";
	std::cout << "Was expecting 86, got " + to_string(norm) << std::endl;
	return false;
}

bool TestsVector3D::Vector3DNormalization()
{
	Vector3D vector = Vector3D(5, 6, -5);

	vector.Normalize();
	Vector3D intendedVector = Vector3D(5 / sqrt(86), 6 / sqrt(86), -5 / sqrt(86));

	// handle float approximation
	if ((vector - intendedVector).Norm() < 0.001f)
	{
		std::cout << "Normalization : Success" << std::endl;
		return true;
	}

	std::cout << "Normalization : Fail. ";
	std::cout << "Was expecting " + intendedVector.toString() + ", got " + vector.toString() << std::endl;
	return false;
}

bool TestsVector3D::Vector3DVectorProduct()
{
	Vector3D firstVector = Vector3D(5, 6, -5);
	Vector3D secondVector = Vector3D(7, -4, -2.6);

	Vector3D productVector = firstVector ^ secondVector;
	Vector3D intendedVector = Vector3D(-35.6, -22, -62);

	if (productVector == intendedVector)
	{
		std::cout << "Vector Product : Success" << std::endl;
		return true;
	}

	std::cout << "Vector Product : Fail. ";
	std::cout << "Was expecting (-35.6, -22, -62), got " + productVector.toString() << std::endl;
	return false;
}

bool TestsVector3D::Vector3Dfloatfloat()
{
	Vector3D vector = Vector3D(0, 1, 0);
	float f1 = 12.65;
	float f2 = 16.69;

	Vector3D intendedVector = Vector3D(0, f1 * f2, 0);
	Vector3D result = vector * f1 * f2;

	if (result == intendedVector)
	{
		std::cout << "Vector Product double float : Success" << std::endl;
		return true;
	}

	std::cout << "Vector Product : Fail. ";
	std::cout << "Was expecting " << intendedVector.toString() << ", got " << result.toString() << std::endl;
	return false;
}