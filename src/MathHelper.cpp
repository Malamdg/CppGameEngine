#include "MathHelper.h"
#include "Vector3D.h"

Vector3D integrate(Vector3D v, float time, Vector3D v0) {
	// rectangle aria on one frame using its duration => all frames make sum on mvt duration
	return v * time + v0;
}
