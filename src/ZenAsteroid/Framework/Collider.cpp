/*
 * Collider.cpp
 *
 *  Created on: Apr 26, 2026
 *      Author: NMc
 */

#include "Collider.h"

Collider::Collider() = default;

Collider::Collider(Vector2f iLocation, float iRadius) {
	mLocation = iLocation;
	mRadius = iRadius;
}

Collider::~Collider() {
	// TODO Auto-generated destructor stub
}

