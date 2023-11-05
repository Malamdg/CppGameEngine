#pragma once
#include "Vector3D.h"
#include "Matrix3.h"
#include "Matrix4.h"

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



	// Matrix 3

	/*
	execute all the test on Matrix3
	display the number of tests passed and the number of tests failed
	*/
	static void ExecuteMatrix3Tests();

	/*
	test the construtor method of Matrix3
	@return true if the Matrix3 created is ((0, 0, 0), (0, 0, 0), (0, 0, 0))
	*/
	static bool Matrix3EmtpyConstructor();

	/*
	test the zeros method of Matrix3
	@return true if the Matrix3 is ((0, 0, 0), (0, 0, 0), (0, 0, 0))
	*/
	static bool Matrix3Zeros();

	/*
	test the id method of Matrix3
	@return true if the Matrix3 is ((1, 0, 0), (0, 1, 0), (0, 0, 1))
	*/
	static bool Matrix3Id();

	/*
	test the getter and setter of a Matrix3
	@return true if the Matrix3 is really accessed and modified
	*/
	static bool AccessingAndModifyingMatrix3();

	/*
	test the addition of two Matrix3
	@return true if the sum is correct
	*/
	static bool Matrix3Addition();

	/*
	test the substraction of two Matrix3
	@return true if the substraction is correct
	*/
	static bool Matrix3Soustraction();

	/*
	test the float and Matrix product with a Matrix3
	@return true if the float*Matrix product is correctly computed
	*/
	static bool Matrix3FloatProduct();

	/*
	test the Matrix and Matrix product with a Matrix3
	@return true if the Matrix*Matrix product is correctly computed
	*/
	static bool Matrix3MatrixProduct();

	/*
	test inverse computation of a Matrix3
	@return true if the inverse is correctly computed
	*/
	static bool Matrix3Inverse();

	/*
	test invert computation of a Matrix3
	@return true if the inverse is correctly computed
	*/
	static bool Matrix3Invert();

	/*
	test the transposition of a Matrix3
	@return true if the transposition is correctly computed
	*/
	static bool Matrix3Transpose();

	/*
	test the determinant computation of a Matrix3
	@return true if the determinant is correctly computed
	*/
	static bool Matrix3Determinant();



	// Matrix 4

	/*
	execute all the test on Matrix4
	display the number of tests passed and the number of tests failed
	*/
	static void ExecuteMatrix4Tests();

	/*
	test the construtor method of Matrix4
	@return true if the Matrix4 created is ((0, 0, 0), (0, 0, 0), (0, 0, 0))
	*/
	static bool Matrix4EmtpyConstructor();

	/*
	test the zeros method of Matrix4
	@return true if the Matrix4 is ((0, 0, 0), (0, 0, 0), (0, 0, 0))
	*/
	static bool Matrix4Zeros();

	/*
	test the id method of Matrix4
	@return true if the Matrix4 is ((1, 0, 0), (0, 1, 0), (0, 0, 1))
	*/
	static bool Matrix4Id();

	/*
	test the getter and setter of a Matrix4
	@return true if the Matrix4 is really accessed and modified
	*/
	static bool AccessingAndModifyingMatrix4();

	/*
	test the addition of two Matrix4
	@return true if the sum is correct
	*/
	static bool Matrix4Addition();

	/*
	test the substraction of two Matrix4
	@return true if the substraction is correct
	*/
	static bool Matrix4Soustraction();

	/*
	test the float and Matrix product with a Matrix4
	@return true if the float*Matrix product is correctly computed
	*/
	static bool Matrix4FloatProduct();

	/*
	test the Matrix and Matrix product with a Matrix4
	@return true if the Matrix*Matrix product is correctly computed
	*/
	static bool Matrix4MatrixProduct();

	/*
	test inverse computation of a Matrix4
	@return true if the inverse is correctly computed
	*/
	static bool Matrix4Inverse();

	/*
	test invert computation of a Matrix3
	@return true if the inverse is correctly computed
	*/
	static bool Matrix4Invert();


	/*
	test the transposition of a Matrix4
	@return true if the transposition is correctly computed
	*/
	static bool Matrix4Transpose();

	/*
	test the determinant computation of a Matrix4
	@return true if the determinant is correctly computed
	*/
	static bool Matrix4Determinant();
};

