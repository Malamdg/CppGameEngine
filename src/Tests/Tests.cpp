#include "Tests.h"

void Tests::ExecuteTests()
{
	TestsVector3D::ExecuteTests();
	TestsQuaternion::ExecuteTests();
	TestsMatrix3::ExecuteTests();
	TestsMatrix4::ExecuteTests();
}