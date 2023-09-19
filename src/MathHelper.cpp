#include "MathHelper.h"
#include "Vector3D.h"

Vector3D integrate(function<Vector3D(float)> f, float interval[2], int N)
{
	Vector3D u = Vector3D();
	float step = (interval[1] - interval[0]) / N; // algorithm integration step, width of a rectangle

	// Midpoint integration precise enough with min 50 rectangles
	for (int i = 0; i < N; i++) {
		u += f((2 * i + 1) * step / 2) * step;
	}

	return u;
}
