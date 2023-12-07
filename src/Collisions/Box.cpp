#pragma once

#include "Box.h"
#include <Matrix3.h>

Box::Box(Vector3D* position, Vector3D* axe1, Vector3D* axe2, Vector3D* axe3)
	:
	Collider(position),
	m_right(axe1),
	m_top(axe2),
	m_foward(axe3)
{}

Box::~Box()
{
	delete m_right;
	delete m_top;
	delete m_foward;
}

void Box::setRotation(Quaternion* rotation)
{
	Matrix3 rotationM = Matrix3::FromQuaternion(*rotation);
	*m_right = rotationM * *m_right;
	*m_top = rotationM * *m_top;
	*m_foward = rotationM * *m_foward;
}

Vector3D Box::getRight() { return *m_right; }
Vector3D Box::getTop() { return *m_top; }
Vector3D Box::getForward() { return *m_foward; }
Vector3D Box::getAxis(int i) 
{
	if (i == 0) return getRight();
	if (i == 1) return getTop();
	if (i == 2) return getForward();
	else return Vector3D();
}

bool Box::intersect(Collider* collider, Vector3D* direction, float* penetration)
{
	if (instanceof<Box>(collider))
	{
		return intersection((Box*)collider, direction, penetration);
	}
	if (instanceof<Plane>(collider))
	{
		return intersection((Plane*)collider, direction, penetration);
	}
	return false;
}

bool Box::intersection(Box* collider, Vector3D* direction, float* penetration)
{

	Vector3D boxDir = getPosition() - collider->getPosition();

	float minPenetration = FLT_MAX;

	for (int i = 0; i < 2; i++)
	{
		Vector3D currentAxe = getAxis(i);
		float projCA = currentAxe.Norm();

		currentAxe.Normalize();

		float projDirection = abs(boxDir * currentAxe);

		for (int j = 0; j < 2; j++)
		{
			Vector3D otherAxe = collider->getAxis(j);
			float projOA = abs(otherAxe * currentAxe);

			float currentPenetration = projCA + projOA - projDirection;
			if (currentPenetration > 0)
			{
				if (currentPenetration < minPenetration)
				{
					minPenetration = currentPenetration;
					*direction = otherAxe;
					*penetration = currentPenetration;
				}
			}
			else return false;
		}
	}

	return true;
}
bool Box::intersection(Plane* collider, Vector3D* direction, float* penetration)
{
	return false;
}