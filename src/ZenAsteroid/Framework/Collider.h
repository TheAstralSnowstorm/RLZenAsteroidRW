/*
 * Collider.h
 *
 *  Created on: Apr 26, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_FRAMEWORK_COLLIDER_H_
#define ZENASTEROID_FRAMEWORK_COLLIDER_H_

#include "MathUtilities.h"

class Collider {
public:
	Collider();

	Vector2f mLocation = (Vector2f){0.0, 0.0};
	float mRadius = 1.0;
	bool mDrawTest = false;

	Collider(Vector2f iLocation, float iRadius);
	virtual ~Collider();
};

#endif /* ZENASTEROID_FRAMEWORK_COLLIDER_H_ */
