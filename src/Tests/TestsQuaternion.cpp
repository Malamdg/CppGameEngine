#include "TestsQuaternion.h"

void TestsQuaternion::ExecuteTests()
{
	int success = 0;
	int fail = 0;

	std::cout << "--- Quaternion ---" << std::endl << std::endl;

	QuaternionEmptyConstructor() ? success++ : fail++;
	QuaternionFromVectorConstructor() ? success++ : fail++;
	QuaternionEulerConstructor() ? success++ : fail++;
	QuaternionIdentityConstructor() ? success++ : fail++;
	QuaternionNorm() ? success++ : fail++;
	QuaternionNormalize() ? success++ : fail++;
	QuaternionNegation() ? success++ : fail++;
	QuaternionInverse() ? success++ : fail++;
	QuaternionConjugue() ? success++ : fail++;
	QuaternionMultiplicationBetweenQuaternions() ? success++ : fail++;
	QuaternionMultipticationWithFloat() ? success++ : fail++;
	QuaternionSum() ? success++ : fail++;
	QuaternionDifference() ? success++ : fail++;
	QuaternionScalarProduct() ? success++ : fail++;
	QuaternionExponentiation() ? success++ : fail++;
	QuaternionSlerp0() ? success++ : fail++;
	QuaternionSlerp1() ? success++ : fail++;
	QuaternionSlerpX() ? success++ : fail++;

	std::cout << to_string(success) + " success, " + to_string(fail) + " fail" << std::endl << std::endl;
}

bool TestsQuaternion::QuaternionEmptyConstructor()
{
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

bool TestsQuaternion::QuaternionFromVectorConstructor()
{
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

bool TestsQuaternion::QuaternionEulerConstructor()
{
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

bool TestsQuaternion::QuaternionIdentityConstructor()
{
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

bool TestsQuaternion::QuaternionNorm()
{
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

bool TestsQuaternion::QuaternionNormalize()
{
	Quaternion quat = Quaternion(1, sin(PI / 2), sin(PI / 10), sin(PI / 40));
	quat.Normalize();
	float intendedNorm = 1;

	if (abs(quat.Norm() - intendedNorm) < 10e-6)
	{
		std::cout << "Quaternion Normalize : Success" << std::endl;
		return true;
	}

	std::cout << "Quaternion Norm : Fail. ";
	std::cout << "Was expecting " << to_string(intendedNorm) << " for the quaternion's norm, got " << to_string(quat.Norm()) << std::endl;


	return false;
}

bool TestsQuaternion::QuaternionNegation()
{
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

bool TestsQuaternion::QuaternionInverse()
{
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

bool TestsQuaternion::QuaternionConjugue()
{
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

bool TestsQuaternion::QuaternionMultiplicationBetweenQuaternions()
{
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

bool TestsQuaternion::QuaternionMultipticationWithFloat()
{
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

bool TestsQuaternion::QuaternionDifference()
{
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

bool TestsQuaternion::QuaternionSum()
{
	Quaternion quat1 = Quaternion(5.f, 6.f, 7.f, -60.f);
	Quaternion quat2 = Quaternion(7.f, -3.f, 30.f, -1.f);
	Quaternion res = quat1 + quat2;
	Quaternion intendedQuat = Quaternion(12.f, 3.f, 37.f, -61.f);

	if (res == intendedQuat)
	{
		std::cout << "Sum Quaternions : Success" << std::endl;
		return true;
	}

	std::cout << "Sums Quaternions : Fail. ";
	std::cout << "Was expecting " << intendedQuat.toString() << ", got " << res.toString() << std::endl;

	return false;
}

bool TestsQuaternion::QuaternionScalarProduct()
{
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

bool TestsQuaternion::QuaternionExponentiation()
{
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

bool TestsQuaternion::QuaternionSlerp0()
{
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

bool TestsQuaternion::QuaternionSlerp1()
{
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

bool TestsQuaternion::QuaternionSlerpX()
{
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