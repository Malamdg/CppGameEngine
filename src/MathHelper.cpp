#include "MathHelper.h"
#include "Vector3D.h"

/*
integrate a vector 
integration over time with Euler alorithm (rectangle method) to get velocity from acceleration and position from velocity.

@param v the vector to integrate, time the current time, v0 the initial velocity

@return the vector integrated
*/
Vector3D integrate(Vector3D v, float time, Vector3D v0) {
	// rectangle area on one frame using its duration => all frames make sum on mvt duration
	return v * time + v0;
}
