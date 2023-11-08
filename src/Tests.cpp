#include "Tests.h"

void Tests::ExecuteTests()
{
	ExecuteVector3DTests();
	ExecuteQuaternionTests();
}

int Tests::nbOfTest = 0;

////////// Vector3D //////////

void Tests::ExecuteVector3DTests()
{
	nbOfTest = 0;
	int success = 0;

	std::cout << "--- Vector3D ---" << std::endl << std::endl;

	success += Vector3DEmtpyConstructor();
	success += AccessingAndModifyingVector3D();
	success += Vector3DAddition();
	success += Vector3DSoustraction();
	success += Vector3DScalarProduct();
	success += Vector3DNorm();
	success += Vector3DNorm2();
	success += Vector3DNormalization();
	success += Vector3DVectorProduct();
	success += Vector3Dfloatfloat();

	std::cout << to_string(success) + " success, " + to_string(nbOfTest - success) + " fail" << std::endl << std::endl;
}

void Tests::ExecuteQuaternionTests()
{
	nbOfTest = 0;
	int success = 0;

	std::cout << "--- Quaternion ---" << std::endl << std::endl;

	success += QuaternionEmptyConstructor();
	success += QuaternionFromVectorConstructor();
	success += QuaternionEulerConstructor();
	success += QuaternionIdentityConstructor();
	success += QuaternionNorm();
	success += QuaternionNegation();
	success += QuaternionInverse();
	success += QuaternionConjugue();
	success += QuaternionMultiplicationBetweenQuaternions();
	success += QuaternionMultipticationWithFloat();
	success += QuaternionDifference();
	success += QuaternionScalarProduct();
	success += QuaternionExponentiation();
	success += QuaternionSlerp0();
	success += QuaternionSlerp1();
	success += QuaternionSlerpX();

	std::cout << to_string(success) + " success, " + to_string(nbOfTest - success) + " fail" << std::endl;
}

bool Tests::Vector3DEmtpyConstructor()
{
	nbOfTest++;
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

bool Tests::AccessingAndModifyingVector3D()
{
	nbOfTest++;
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

bool Tests::Vector3DAddition()
{
	nbOfTest++;
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

bool Tests::Vector3DSoustraction()
{
	nbOfTest++;

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

bool Tests::Vector3DScalarProduct()
{
	nbOfTest++;

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

bool Tests::Vector3DNorm()
{
	nbOfTest++;

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

bool Tests::Vector3DNorm2()
{
	nbOfTest++;

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

bool Tests::Vector3DNormalization()
{
	nbOfTest++;

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

bool Tests::Vector3DVectorProduct()
{
	nbOfTest++;

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

bool Tests::Vector3Dfloatfloat()
{
	nbOfTest++;

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

bool Tests::QuaternionEmptyConstructor()
{
	nbOfTest++;
	Quaternion quat = Quaternion();
	Quaternion intendedQuat = Quaternion(0, 0, 0, 0);

	if (quat == intendedQuat)
	{
		std::cout << "Empty Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Empty Constructor : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << quat.toString() << std::endl;
	return false;
}

bool Tests::QuaternionFromVectorConstructor()
{
	nbOfTest++;
	Vector3D v = Vector3D(.5f, .5f, .5f);
	Quaternion quat = Quaternion(.5f, v);
	Quaternion intendedQuat = Quaternion(.5f, .5f, .5f, .5f);

	if (quat == intendedQuat)
	{
		std::cout << "Constructor from Vector3D : Success" << std::endl;
		return true;
	}

	std::cout << "Empty Constructor : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << quat.toString() << std::endl;
	return false;
}

bool Tests::QuaternionEulerConstructor()
{
	nbOfTest++;

	Quaternion quat = Quaternion::Euler(3.14, -0.63, .16);
	
	Quaternion intendedQuat = Quaternion(0.0255136, 0.9477354, -0.0762285, -0.308765); // <- Valeure trouvées via https://www.andre-gaschler.com/rotationconverter/

	if (quat.EqualsWithTolerance(intendedQuat))
	{
		std::cout << "Euler Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Euler Constructor : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << quat.toString() << std::endl;

	return false;
}

bool Tests::QuaternionIdentityConstructor()
{
	nbOfTest++;

	Quaternion quat = Quaternion::Identity();
	Quaternion intendedQuat = Quaternion(1, 0, 0, 0);

	if (quat == intendedQuat)
	{
		std::cout << "Identity Constructor : Success" << std::endl;
		return true;
	}

	std::cout << "Identity Constructor : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << quat.toString() << std::endl;

	return false;
}

bool Tests::QuaternionNorm()
{
	nbOfTest++;

	Quaternion quat = Quaternion(1, sin(PI / 2), sin(PI / 10), sin(PI / 40));
	float intendedNorm = sqrt(2 + pow(sin(PI / 10), 2) + pow(sin(PI / 40), 2));

	if (abs(quat.Norm() - intendedNorm) < 10e-6)
	{
		std::cout << "Quaternion Norm : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion Norm : Fail. ";
	std::cout << "Was expecting " << to_string(intendedNorm) << ", got " << to_string(quat.Norm()) << std::endl;


	return false;
}

bool Tests::QuaternionNegation()
{
	nbOfTest++;
	Quaternion quat = Quaternion(.5f, 6, 7.3f, -60.f);
	Quaternion intendedQuat = Quaternion(-.5f, -6, -7.3f, 60.f);

	if (quat.Negation() == intendedQuat)
	{
		std::cout << "Negation Quaternion : Success" << std::endl;
		return true;
	}

	std::cout << "Negation Quaternion : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << quat.Negation().toString() << std::endl;
	return false;
}

bool Tests::QuaternionInverse()
{
	nbOfTest++;

	Quaternion quat = Quaternion(5.f, -6.f, 8.f, 10.f);
	Quaternion invQuat = quat.Inverse();
	Quaternion intendedQuat = quat.Conjugue() * (1/quat.Norm());

	if ( abs(invQuat.getW() - intendedQuat.getW()) < 1e-10 
		&& abs(invQuat.getX() - intendedQuat.getX()) < 1e-10
		&& abs(invQuat.getY() - intendedQuat.getY()) < 1e-10
		&& abs(invQuat.getZ() - intendedQuat.getZ()) < 1e-10)
	{
		std::cout << "Inverse Quaternion : Success" << std::endl;
		return true;
	}

	std::cout << "Inverse Quaternion : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << invQuat.toString() << std::endl;
	
	return false;
}

bool Tests::QuaternionConjugue()
{
	nbOfTest++;

	Quaternion quat = Quaternion(.5f, 6, 7.3f, -60.f);
	Quaternion intendedQuat = Quaternion(.5f, -6, -7.3f, 60.f);

	if (quat.Conjugue() == intendedQuat)
	{
		std::cout << "Conjugue Quaternion : Success" << std::endl;
		return true;
	}

	std::cout << "Conjugue Quaternion : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << quat.Conjugue().toString() << std::endl;
	
	return false;
}

bool Tests::QuaternionMultiplicationBetweenQuaternions()
{
	nbOfTest++;

	Quaternion quat1 = Quaternion(5.f, 6.f, 7.f, -60.f);
	Quaternion quat2 = Quaternion(7.f, -3.f, 30.f, -1.f);
	Quaternion res = quat1 * quat2;
	Quaternion intendedQuat = Quaternion(-217.f, 1820.f, 385.f, -224.f);

	if (res == intendedQuat)
	{
		std::cout << "Product Quaternions : Success" << std::endl;
		return true;
	}

	std::cout << "Product Quaternions : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool Tests::QuaternionMultipticationWithFloat()
{
	nbOfTest++;

	Quaternion quat = Quaternion(.5f, 6.f, 7.f, -60.f);
	Quaternion res = quat * 5;
	Quaternion intendedQuat = Quaternion(2.5f, 30.f, 35.f, -300.f);

	if (res == intendedQuat)
	{
		std::cout << "Product Quaternion with float : Success" << std::endl;
		return true;
	}

	std::cout << "Product Quaternion with float : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool Tests::QuaternionDifference()
{
	nbOfTest++;

	Quaternion quat1 = Quaternion(5.f, 6.f, 7.f, -60.f);
	Quaternion quat2 = Quaternion(7.f, -3.f, 30.f, -1.f);
	Quaternion res = quat1 - quat2;
	Quaternion intendedQuat = Quaternion(287.f, 1736.f, 287.f, 616.f);

	if (res == intendedQuat)
	{
		std::cout << "Difference Quaternions : Success" << std::endl;
		return true;
	}

	std::cout << "Difference Quaternions : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool Tests::QuaternionScalarProduct()
{
	nbOfTest++;

	Quaternion quat1 = Quaternion(5.f, 6.f, 7.f, -60.f);
	Quaternion quat2 = Quaternion(7.f, -3.f, 30.f, -1.f);
	float res = quat1.dot(quat2);
	float intendedFloat = 287.f;

	if (res == intendedFloat)
	{
		std::cout << "Scalar Product Quaternions : Success" << std::endl;
		return true;
	}

	std::cout << "Scalar Product Quaternions : Fail. ";
	std::cout << "Was expecting " << to_string(intendedFloat) << ", got " << to_string(res) << std::endl;

	return false;
}

bool Tests::QuaternionExponentiation()
{
	nbOfTest++;

	Quaternion quat1 = Quaternion::Euler(3, 1, -2);
	Quaternion res = quat1^5;
	Quaternion intendedQuat = Quaternion(0.77461690052, -0.31231549002, -0.53051057326, -0.144866000); // Calcul fait à la main, avec accumulation d'erreur d'approximation d'ou la tolerance relativement haute

	if (res.EqualsWithTolerance(intendedQuat, 1e-5))
	{
		std::cout << "Exponentiation Quaternion : Success" << std::endl;
		return true;
	}

	std::cout << "Exponentiation Quaternion : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool Tests::QuaternionSlerp0()
{
	nbOfTest++;

	Quaternion q0 = Quaternion::Euler(0, 0, 0);
	Quaternion q1 = Quaternion::Euler(PI, PI, PI);

	Quaternion res = Quaternion::slerp(q0, q1, 0);

	if (res == q0)
	{
		std::cout << "Quaternion slerp 0 : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion slerp 0 : Fail. ";
	std::cout << "Was expecting " << q0.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool Tests::QuaternionSlerp1()
{
	nbOfTest++;

	Quaternion q0 = Quaternion::Euler(0, 0, 0);
	Quaternion q1 = Quaternion::Euler(PI, PI, PI);

	Quaternion res = Quaternion::slerp(q0, q1, 1);

	if (res == q1)
	{
		std::cout << "Quaternion slerp 1 : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion slerp 1 : Fail. ";
	std::cout << "Was expecting " << q1.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool Tests::QuaternionSlerpX()
{
	nbOfTest++;

	Quaternion q0 = Quaternion::Euler(0, 0, 0);
	Quaternion q1 = Quaternion::Euler(PI, PI, PI);
	Quaternion qX = Quaternion::Euler(PI / 2, PI / 2, PI / 2);

	Quaternion res = Quaternion::slerp(q0, q1, .5);

	if (res == qX)
	{
		std::cout << "Quaternion slerp X : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion slerp X : Fail. ";
	std::cout << "Was expecting " << qX.toString() << ", got " << res.toString() << std::endl;

	return false;
}