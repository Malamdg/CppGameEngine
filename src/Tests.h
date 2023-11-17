#pragma once

#include "DataStructures/Matrix3.h"
#include "DataStructures/Matrix4.h"
#include "DataStructures/Vector3D.h"
#include "DataStructures/Quaternion.h"

static class Tests
{
public:
	/*
	execute all the test
	*/
	static void ExecuteTests();

private:
	static int nbOfTest;

	// Vector3D

	/*
	execute all the test on Vector3D
	display the number of tests passed and the number of tests failed
	*/
	static void ExecuteVector3DTests();

	/*
	execute all the test on Quaternion
	display the number of tests passed and the number of tests failed
	*/
	static void ExecuteQuaternionTests();

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
