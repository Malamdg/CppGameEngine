#include "MathHelper.h"
#include "Vector3D.h"
#include "ofMain.h"

float integrate(float x, float x0) {
	float time, fps;
	fps = ofGetFrameRate();
	// avoid division by zero
	time = fps == 0 ? -1 : 1 / fps;

	if (time == -1) {
		return x;
	}

	// rectangle aria 
	return x * time + x0;
}

Vector3D integrate(Vector3D v, Vector3D v0) {
	Vector3D u = Vector3D();
	for (int i = 0; i < 4; i++) {
		u[i] = integrate(v[i], v0[i]);
	}

	return u;
}
