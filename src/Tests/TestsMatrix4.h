#pragma once

#include "DataStructures/Matrix4.h"

static class TestsMatrix4
{
public:
	/*
	execute all the test
	*/
	static void ExecuteTests();

private:
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
	test the Matrix and Matrix product with a Matrix4
	@return true if the Matrix*Matrix product is correctly computed
	*/
	static bool Matrix4MatrixProduct();

	/*
	test the float and Matrix product with a Matrix4
	@return true if the float*Matrix product is correctly computed
	*/
	static bool Matrix4FloatProduct();
	
	/*
	test the float and Matrix product with a Matrix4
	@return true if the float*Matrix product is correctly computed
	*/
	static bool Matrix4DoubleFloatProduct();

	/*
	test the determinant computation of a Matrix4
	@return true if the determinant is correctly computed
	*/
	static bool Matrix4Determinant();

	/*
	test invert computation of a Matrix3
	@return true if the inverse is correctly computed
	*/
	static bool Matrix4Invert();

	/*
	test inverse computation of a Matrix4
	@return true if the inverse is correctly computed
	*/
	static bool Matrix4Inverse();

	/*
	test the transposition of a Matrix4
	@return true if the transposition is correctly computed
	*/
	static bool Matrix4Transpose();

	/*
	test the transposition of a Matrix4
	@return true if the transposition is correctly computed
	*/
	static bool Matrix4Transposed();
};
