/*
 * Meteor.h
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_METEOR_H_
#define ZENASTEROID_METEOR_H_

#include "Framework/Collider.h"
#include "Framework/MathUtilities.h"

class Meteor {
public:
	Meteor();

	Vector2f MeteorLocation = (Vector2f){320, 240};
	float MeteorRotation = 0.0;
	Vector2f MeteorVelocity = (Vector2f){1, 1};
	float MeteorSpin = 0.0;
	Matrix3f mTransform;
	short MeteorSize = 3;
	Collider mCollision;

	Meteor(Vector2f InitPosition, float InitAngle, Vector2f InitVelocity, float InitSpin, short InitSize);
	virtual ~Meteor();

	float mLargeMeteorScale = 1.0;
	float mMediumMeteorScale = 0.85714285714285714285714285714286;
	float mSmallMeteorScale = 0.75;

	float mCurrentScale = 1.0;

	void UpdateMeteor();
	bool CheckCollisions();
	void DrawMeteor();

	//char mDebugShowSize[2] = {'0', 0};

	//void DrawDebugMisc();
};

#endif /* ZENASTEROID_METEOR_H_ */
