#pragma once

#include "DataStructures/Quaternion.h"

static class TestsQuaternion
{
public:
	/*
	execute all the test
	*/
	static void ExecuteTests();

private:
	/*
	test the constructor method of Quaternion
	@return true if the composant of the Quaternion are null
	*/
	static bool QuaternionEmptyConstructor();

	/*
	test the constructor method of Quaternion from a vector
	@return true if the composant of the Quaternion match the component of the vector
	*/
	static bool QuaternionFromVectorConstructor();

	/*
	test the constructor method of Quaternion from an angle
	@return true if the Quaternion matches te angle
	*/
	static bool QuaternionEulerConstructor();

	/*
	test the identity constructor of the Quaternion
	@return true if the quaternion is (1, 0, 0, 0)
	*/
	static bool QuaternionIdentityConstructor();

	/*
	test the computation of the Quaternion's norm
	@return true if the norm is correctly computed
	*/
	static bool QuaternionNorm();

	/*
	test the normalization for the Quaternion
	@return true if the normalization is correctly computed
	*/
	static bool QuaternionNormalize();

	/*
	test the computation of the Quaternion's negation
	@return true if the negation is correctly computed
	*/
	static bool QuaternionNegation();

	/*
	test the computation of the Quaternion's inverse
	@return true if the inverse is correctly computed
	*/
	static bool QuaternionInverse();

	/*
	test the computation of the Quaternion's conjugue
	@return true if the conjugue is correctly computed
	*/
	static bool QuaternionConjugue();

	/*
	test the dot product of two Quaternions
	@return true if the product is correctly computed
	*/
	static bool QuaternionMultiplicationBetweenQuaternions();

	/*
	test the product of a Quaternion with a float
	@return true if the product is correctly computed
	*/
	static bool QuaternionMultipticationWithFloat();

	/*
	test the sum of two Quaternions
	@return true if the sum is correctly computed
	*/
	static bool QuaternionSum();

	/*
	test the difference between two Quaternions
	@return true if the difference is correctly computed
	*/
	static bool QuaternionDifference();

	/*
	test the scalar product of two Quaternions
	@return true if the scalar product is correctly computed
	*/
	static bool QuaternionScalarProduct();

		/*
	test the exponentiation of a Quaternion
	@return true if the exponentiation is correctly computed
	*/
	static bool QuaternionExponentiation();

	/*
	test the Spherical Linear Interpolation with the first borderline case
	@return true if the interpolation is correctly computed
	*/
	static bool QuaternionSlerp0();
	/*
	test the Spherical Linear Interpolation with the second borderline case
	@return true if the interpolation is correctly computed
	*/
	static bool QuaternionSlerp1();
	/*
	test the Spherical Linear Interpolation intermediate
	@return true if the interpolation is correctly computed
	*/
	static bool QuaternionSlerpX();
};
