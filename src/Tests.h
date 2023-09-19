#pragma once

class Tests
{
public:
	static void ExecuteTests();

private:
	// Vector3D
	static void ExecuteVector3DTests();

	static bool Vector3DEmtpyConstructor();
	static bool AccessingAndModifyingVector3D();
	static bool Vector3DAddition();
	static bool Vector3DSoustraction();
	static bool Vector3DScalarProduct();
	static bool Vector3DNorm();
	static bool Vector3DNorm2();
	static bool Vector3DNormalization();
	static bool Vector3DVectorProduct();
};

