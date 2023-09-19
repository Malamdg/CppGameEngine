#pragma once
#include "Vector3D.h"

Vector3D integrate(function<Vector3D(float)> f, float interval[2], int N = 50);
