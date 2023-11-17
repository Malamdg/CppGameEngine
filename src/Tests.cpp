#include "Tests.h"

void Tests::ExecuteTests()
{
	ExecuteVector3DTests();
	ExecuteMatrix3Tests();
	ExecuteMatrix4Tests();
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
	
	Quaternion intendedQuat = Quaternion(0.0255136, 0.9477354, -0.0762533, -0.308765); // <- Valeur trouv�es via https://www.andre-gaschler.com/rotationconverter/

	if (quat.EqualsWithTolerance(intendedQuat, 10e-5))
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
	Quaternion intendedQuat = Quaternion(0.77461690052, -0.31231549002, -0.53051057326, -0.144866000); // Calcul fait � la main, avec accumulation d'erreur d'approximation d'ou la tolerance relativement haute

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

	Quaternion q0 = Quaternion(1, 0, 0, 0);
	Quaternion q1 = Quaternion(0.086, -0.030, -0.934, -0.345);
	Quaternion intendedQuat = Quaternion(0.7368853371, -0.0203559485, -0.6337485312, -0.2340934082); // Valeur trouv�es via https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm

	Quaternion res = Quaternion::slerp(q0, q1, .5);

	if (res.EqualsWithTolerance(intendedQuat))
	{
		std::cout << "Quaternion slerp X : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion slerp X : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

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
	
	Quaternion intendedQuat = Quaternion(0.0255136, 0.9477354, -0.0762533, -0.308765); // <- Valeur trouv�es via https://www.andre-gaschler.com/rotationconverter/

	if (quat.EqualsWithTolerance(intendedQuat, 10e-5))
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
	Quaternion intendedQuat = Quaternion(0.77461690052, -0.31231549002, -0.53051057326, -0.144866000); // Calcul fait � la main, avec accumulation d'erreur d'approximation d'ou la tolerance relativement haute

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

	Quaternion q0 = Quaternion(1, 0, 0, 0);
	Quaternion q1 = Quaternion(0.086, -0.030, -0.934, -0.345);
	Quaternion intendedQuat = Quaternion(0.7368853371, -0.0203559485, -0.6337485312, -0.2340934082); // Valeur trouv�es via https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm

	Quaternion res = Quaternion::slerp(q0, q1, .5);

	if (res.EqualsWithTolerance(intendedQuat))
	{
		std::cout << "Quaternion slerp X : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion slerp X : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

	return false;
}


////////// Matrix3 //////////

void Tests::ExecuteMatrix3Tests()
{
	int nbOfTest = 16;
	int success = 0;

	std::cout << "Matrix3 : " << std::endl << std::endl;

	success += Matrix3EmtpyConstructor();
	success += Matrix3VectorConstructor();
	success += Matrix3Zeros();
	success += Matrix3Id();
	success += AccessingAndModifyingMatrix3();
	success += Matrix3Addition();
	success += Matrix3Soustraction();
	success += Matrix3MatrixProduct();
	success += Matrix3Vector3DProduct();
	success += Matrix3FloatProduct();
	success += Matrix3DoubleFloatProduct();
	success += Matrix3Determinant();
	success += Matrix3Invert();
	success += Matrix3Inverse();
	success += Matrix3Transpose();
	success += Matrix3Transposed();

	std::cout << to_string(success) + " success, " + to_string(nbOfTest - success) + " fail" << std::endl << std::endl;
}

bool Tests::Matrix3EmtpyConstructor()
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

bool Tests::Matrix3VectorConstructor()
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

bool Tests::Matrix3Zeros()
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

bool Tests::Matrix3Id()
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

bool Tests::AccessingAndModifyingMatrix3()
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

bool Tests::Matrix3MatrixProduct()
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

bool Tests::Matrix3Vector3DProduct()
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

bool Tests::Matrix3FloatProduct()
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

bool Tests::Matrix3DoubleFloatProduct()
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

bool Tests::Matrix3Addition()
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

bool Tests::Matrix3Soustraction()
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

bool Tests::Matrix3Determinant()
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

bool Tests::Matrix3Invert()
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

bool Tests::Matrix3Inverse()
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

bool Tests::Matrix3Transpose()
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

bool Tests::Matrix3Transposed()
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

////////// Matrix4 //////////

void Tests::ExecuteMatrix4Tests()
{
	int nbOfTest = 14;
	int success = 0;

	std::cout << "Matrix4 : " << std::endl << std::endl;

	success += Matrix4EmtpyConstructor();
	success += Matrix4Zeros();
	success += Matrix4Id();
	success += AccessingAndModifyingMatrix4();
	success += Matrix4Addition();
	success += Matrix4Soustraction();
	success += Matrix4MatrixProduct();
	success += Matrix4FloatProduct();
	success += Matrix4DoubleFloatProduct();
	success += Matrix4Determinant();
	success += Matrix4Invert();
	success += Matrix4Inverse();
	success += Matrix4Transpose();
	success += Matrix4Transposed();


	std::cout << to_string(success) + " success, " + to_string(nbOfTest - success) + " fail" << std::endl << std::endl;
}

bool Tests::Matrix4EmtpyConstructor()
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

bool Tests::Matrix4Zeros()
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

bool Tests::Matrix4Id()
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

bool Tests::AccessingAndModifyingMatrix4()
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

bool Tests::Matrix4Addition()
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

bool Tests::Matrix4Soustraction()
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

bool Tests::Matrix4MatrixProduct()
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

bool Tests::Matrix4FloatProduct()
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

bool Tests::Matrix4DoubleFloatProduct()
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

bool Tests::Matrix4Determinant()
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

bool Tests::Matrix4Invert()
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

bool Tests::Matrix4Inverse()
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

bool Tests::Matrix4Transpose()
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

bool Tests::Matrix4Transposed()
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




