#pragma once

#include "DataStructures/Matrix3.h"

static class TestsMatrix3
{
public:
	/*
	execute all the test
	*/
	static void ExecuteTests();

private:
	/*
	test the empty constructor method of Matrix3
	@return true if the Matrix3 created is ((0, 0, 0), (0, 0, 0), (0, 0, 0))
	*/
	static bool Matrix3EmtpyConstructor();

	/*
	test the constructor method of Matrix3 with Vector3D
	@return true if the Matrix3 is correctly created
	*/
	static bool Matrix3VectorConstructor();

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
	test the Matrix and Matrix product with a Matrix3
	@return true if the Matrix*float product is correctly computed
	*/
	static bool Matrix3MatrixProduct();

	/*
	test the Matrix and Matrix product with a Matrix3
	@return true if the Matrix*float product is correctly computed
	*/
	static bool Matrix3Vector3DProduct();

	/*
	test product with a M
	@return true if the float*Matrix product is correctly computed
	*/
	static bool Matrix3FloatProduct();
	
	/*
	test the float and Matrix product with a Matrix3
	@return true if the float*Matrix product is correctly computed
	*/
	static bool Matrix3DoubleFloatProduct();

	/*
	test the determinant computation of a Matrix3
	@return true if the determinant is correctly computed
	*/
	static bool Matrix3Determinant();

	/*
	test invert computation of a Matrix3
	@return true if the inverse is correctly computed
	*/
	static bool Matrix3Invert();

	/*
	test inverse computation of a Matrix3
	@return true if the inverse is correctly computed
	*/
	static bool Matrix3Inverse();

	/*
	test the transposition of a Matrix3
	@return true if the transposition is correctly computed
	*/
	static bool Matrix3Transpose();	
	
	/*
	test the transposition of a Matrix3
	@return true if the transposition is correctly computed
	*/
	static bool Matrix3Transposed();
};
