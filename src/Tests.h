#pragma once

class Tests
{
public:
	/*
	execute all the test
	*/
	static void ExecuteTests();

private:
	// Vector3D

	/*
	execute all the test on Vector3D
	display the number of tests passed and the number of tests failed
	*/
	static void ExecuteVector3DTests();

	/*
	test the construtor method of Vector3D
	@return true if the vector created is (0, 0, 0)
	*/
	static bool Vector3DEmtpyConstructor();

	/*
	test the getter and setter of a Vector3D
	@return true if the vector is really accessed and modified
	*/
	static bool AccessingAndModifyingVector3D();

	/*
	test the addition of two Vector3D
	@return true if the sum is correct
	*/
	static bool Vector3DAddition();

	/*
	test the substraction of two Vector3D
	@return true if the substraction is correct
	*/
	static bool Vector3DSoustraction();

	/*
	test the scalar product of two Vector3D
	@return true if the scalar product is correct
	*/
	static bool Vector3DScalarProduct();

	/*
	test the norm's computation of a Vector3D
	@return true if the norm is correctly computed
	*/
	static bool Vector3DNorm();

	/*
	test the norm 2's computation of a Vector3D
	@return true if the norm is correctly computed
	*/
	static bool Vector3DNorm2();

	/*
	test the normalization of a Vector3D
	@return true if the normalized vector is correctly computed
	*/
	static bool Vector3DNormalization();

	/*
	test the cross product of a Vector3D
	@return true if the cross product is correctly computed
	*/
	static bool Vector3DVectorProduct();

	/*
	test the multiplication of a Vector3D by 2 float (at the same time)
	@return true if the product is correctly computed
	*/
	static bool Vector3Dfloatfloat();
};

