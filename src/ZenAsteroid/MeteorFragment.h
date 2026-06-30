/*
 * MeteorFragment.h
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_METEORFRAGMENT_H_
#define ZENASTEROID_METEORFRAGMENT_H_

#include "Framework/MathUtilities.h"

class MeteorFragment {
public:

	MeteorFragment();

	Vector2f mLocation = (Vector2f){320, 240};
	float mRotation = 0.0;
	float mScale = 4.0;
	Matrix3f mTransform;
	Vector2f mVelocity = (Vector2f){0, 1};
	float mSpin = 0.0;

	MeteorFragment(Vector2f iLocation);
	virtual ~MeteorFragment();

	void Update();
	void Draw();

};

#endif /* ZENASTEROID_METEORFRAGMENT_H_ */
