#pragma once
#include "Vector3D.h"

/*
integrate a function 
integrate the function over an interval with Euler's method using a defined number of steps

@param f, the function to integrate
@param interval[2], the interval over which we integrate
@param N, the number of steps (rectangles)

@return a vector whose components have been integrated
*/
Vector3D integrate(function<Vector3D(float)> f, float interval[2], int N = 50);
float integrate(function<float(float)> f, float interval[2], int N = 50);
