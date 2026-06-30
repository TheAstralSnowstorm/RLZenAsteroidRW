/*
 * Meteor.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#include "Meteor.h"

#include <math.h>
#include <vector>
#include "raylib.h"

#include "Bullet.h"
#include "Framework/MathUtilities.h"
#include "Framework/RNGUtilities.h"
#include "MeteorFragment.h"
#include "Ship.h"

//Vector2f* TransformedPoints = nullptr;

Meteor::Meteor() = default;

Meteor::Meteor(Vector2f InitPosition, float InitAngle, Vector2f InitVelocity, float InitSpin, short InitSize) {
	MeteorLocation = InitPosition;
	MeteorRotation = InitAngle;
	MeteorVelocity = InitVelocity;
	MeteorSpin = InitSpin;
	MeteorSize = InitSize;

	switch (MeteorSize) {
	case 1: {
		mCollision = (Collider){(Vector2f){0.0, 0.0}, 16.0};
		mCurrentScale = mSmallMeteorScale;
		break;
	}
	case 2: {
		mCollision = (Collider){(Vector2f){0.0, 0.0}, 28.0};
		mCurrentScale = mMediumMeteorScale;
		break;
	}
	case 3: {
		mCollision = (Collider){(Vector2f){0.0, 0.0}, 40.0};
		mCurrentScale = mLargeMeteorScale;
		break;
	}
	default: {
		mCollision = (Collider){(Vector2f){0.0, 0.0}, 0.0};
		mCurrentScale = 1.0;
		}
	}
}

Meteor::~Meteor() {

}

extern std::vector<Bullet> gBullets;
extern std::vector<Meteor> meteor;
extern std::vector<MeteorFragment> gMeteorFragments;
extern std::vector<Ship> ship;



const int SmallMeteorPointCount = 12;
Vector2f SmallMeteorPoints[SmallMeteorPointCount] = {	(Vector2f){0.0 , 13.5}, (Vector2f){-9.25 , 16.02}, (Vector2f){-11.69 , 6.75}, (Vector2f){-18.5 , 0.0},
														(Vector2f){-11.69, -6.75}, (Vector2f){-9.25 , -16.02}, (Vector2f){0.0 , -18.5}, (Vector2f){6.75 , -11.69},
														(Vector2f){16.02 , -9.25}, (Vector2f){18.5 , 0.0}, (Vector2f){11.69 , 6.75}, (Vector2f){6.75 , 11.69}};
const int SmallMeteorLineCount = 12;
int SmallMeteorLines[SmallMeteorLineCount][2] = {	{0, 1}, {1, 2}, {2, 3}, {3, 4},
													{4, 5}, {5, 6}, {6, 7}, {7, 8},
													{8, 9}, {9, 10}, {10, 11}, {11, 0}};

const int MediumMeteorPointCount = 16;
Vector2f MediumMeteorPoints[MediumMeteorPointCount] = {	(Vector2f){0.0 , 31.0}, (Vector2f){-9.57 , 23.1}, (Vector2f){-21.92 , 21.92}, (Vector2f){-28.64 , 11.86},
														(Vector2f){-25.0 , 0.0}, (Vector2f){-28.64 , -11.86}, (Vector2f){-17.68 , -17.68}, (Vector2f){-11.86 , -28.64},
														(Vector2f){0.0 , -31.0}, (Vector2f){11.86 , -28.64}, (Vector2f){21.92 , -21.92}, (Vector2f){23.1 , -9.57},
														(Vector2f){31.0 , 0.0}, (Vector2f){28.64 , 11.86}, (Vector2f){17.68 , 17.68}, (Vector2f){9.57 , 23.1}};

const int MediumMeteorLineCount = 16;
int MediumMeteorLines[MediumMeteorLineCount][2] = {	{0, 1}, {1, 2}, {2, 3}, {3, 4},
													{4, 5}, {5, 6}, {6, 7}, {7, 8},
													{8, 9}, {9, 10}, {10, 11}, {11, 12},
													{12, 13}, {13, 14}, {14, 15}, {15, 0}};

const int LargeMeteorPointCount = 20;
Vector2f LargeMeteorPoints[LargeMeteorPointCount] = {	(Vector2f){-0.0 , 36.0}, (Vector2f){-13.6 , 41.85}, (Vector2f){-25.86 , 35.6}, (Vector2f){-29.13 , 21.16},
														(Vector2f){-41.85 , 13.6}, (Vector2f){-36.0 , 0.0}, (Vector2f){-34.24 , -11.13}, (Vector2f){-35.6 , -25.86},
														(Vector2f){-25.86 , -35.6}, (Vector2f){-11.13 , -34.24}, (Vector2f){0.0 , -36.0}, (Vector2f){13.6 , -41.85},
														(Vector2f){21.16, -29.13}, (Vector2f){29.13 , -21.16}, (Vector2f){41.85 , -13.6}, (Vector2f){36.0 , 0.0},
														(Vector2f){34.24 , 11.13}, (Vector2f){29.13 , 21.16}, (Vector2f){25.86 , 35.6}, (Vector2f){11.13 , 34.24}};
const int LargeMeteorLineCount = 20;
int LargeMeteorLines[LargeMeteorLineCount][2] = {	{0, 1}, {1, 2}, {2, 3}, {3, 4},
													{4, 5}, {5, 6}, {6, 7}, {7, 8},
													{8, 9}, {9, 10}, {10, 11}, {11, 12},
													{12, 13}, {13, 14}, {14, 15}, {15, 16},
													{16, 17}, {17, 18}, {18, 19}, {19, 0}};

Vector2f ErrorMeteorPoints[4] = {(Vector2f){-32.0 , -32.0}, (Vector2f){32.0 , -32.0}, (Vector2f){-32.0 , 32.0}, (Vector2f){32.0 , 32.0}};
int ErrorMeteorLines[4][2] = {{0, 1}, {1, 3}, {3, 2}, {2, 0}};

void Meteor::UpdateMeteor() {
	MeteorLocation.X += MeteorVelocity.X * GetFrameTime();
	MeteorLocation.Y += MeteorVelocity.Y * GetFrameTime();
	MeteorLocation.X = fmodf(MeteorLocation.X + 640, 640);
	MeteorLocation.Y = fmodf(MeteorLocation.Y + 480, 480);
	MeteorRotation += MeteorSpin * GetFrameTime();
	mTransform = MathUtilities::SRT2DToMatrix3f((Vector2f){mCurrentScale, mCurrentScale}, MeteorRotation, (Vector2f){MeteorLocation.X, MeteorLocation.Y});
	if (mCollision.mDrawTest) {
		switch (MeteorSize) {
		case 1: {
			DrawCircle(	MeteorLocation.X, 480 - MeteorLocation.Y, mCollision.mRadius * mSmallMeteorScale, (Color){0, 170, 0, 255});
			break;
		}
		case 2: {
			DrawCircle(	MeteorLocation.X, 480 - MeteorLocation.Y, mCollision.mRadius * mMediumMeteorScale, (Color){0, 170, 0, 255});
			break;
		}
		case 3: {
			DrawCircle(	MeteorLocation.X, 480 - MeteorLocation.Y, mCollision.mRadius * mLargeMeteorScale, (Color){0, 170, 0, 255});
			break;
		}
		default: {
			DrawCircle(	MeteorLocation.X, 480 - MeteorLocation.Y, mCollision.mRadius, (Color){0, 170, 0, 255});
			}
		}
	}
	//Meteor::CheckCollisions();
}

bool Meteor::CheckCollisions() {
	for (unsigned int b = 0; b < gBullets.size(); b++) {
		float xDistanceFromBullet = MeteorLocation.X - gBullets[b].mLocation.X;
		float yDistanceFromBullet = MeteorLocation.Y - gBullets[b].mLocation.Y;
		float SumOfColliderRadii = mCollision.mRadius * mCurrentScale + gBullets[b].mCollision.mRadius * gBullets[b].mScale;
		if ((xDistanceFromBullet * xDistanceFromBullet) + (yDistanceFromBullet * yDistanceFromBullet) <= (SumOfColliderRadii * SumOfColliderRadii)) {
			gBullets.erase(gBullets.begin() + b);
			for (unsigned int cnmf = 0; cnmf < 9; cnmf++) {
				gMeteorFragments.push_back({(Vector2f){MeteorLocation.X , MeteorLocation.Y}});
			}
			if (MeteorSize > 1) {
				for (unsigned int cnm = 0; cnm < 3; cnm++) {
					meteor.push_back({	(Vector2f){MeteorLocation.X , MeteorLocation.Y},
										RNGUtilities::whRandom(-3.1415926535897932384626433832795, 3.1415926535897932384626433832795),
										(Vector2f){	RNGUtilities::whRandom(-64.0, 64.0), RNGUtilities::whRandom(-64.0, 64.0)},
										RNGUtilities::whRandom(-3.1415926535897932384626433832795, 3.1415926535897932384626433832795), (short)(MeteorSize - 1)});
				}
			}
			switch (MeteorSize) {
			case 1: {
				ship[0].mScore += 625;
				break;
			}
			case 2: {
				ship[0].mScore += 250;
				break;
			}
			default: {
				ship[0].mScore += 100;
			}
			}
			return true;
		}
	}
	return false;
}

void Meteor::DrawMeteor() {
	/*
	 * May 4, 2026
	 * There is a rendering bug that causes the meteors to change shapes when
	 * meteors are shot. - N. McDown
	 *
	 * RESOLVED May 4, 2026: I was just being an idiot and had forgotten to make
	 * mTransform a member variable up until this point. - N. McDown
	 */
	switch (MeteorSize) {
	case 1: {
		for (int i = 0; i < SmallMeteorLineCount; i++) {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(SmallMeteorPoints[SmallMeteorLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(SmallMeteorPoints[SmallMeteorLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(SmallMeteorPoints[SmallMeteorLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(SmallMeteorPoints[SmallMeteorLines[i][1]], mTransform).Y + 480,
						(Color){255,255,255,255});
		}
		break;
	}
	case 2: {
		for (int i = 0; i < MediumMeteorLineCount; i++) {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(MediumMeteorPoints[MediumMeteorLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(MediumMeteorPoints[MediumMeteorLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(MediumMeteorPoints[MediumMeteorLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(MediumMeteorPoints[MediumMeteorLines[i][1]], mTransform).Y + 480,
						(Color){255,255,255,255});
		}
		break;
	}
	case 3: {
		for (int i = 0; i < LargeMeteorLineCount; i++) {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(LargeMeteorPoints[LargeMeteorLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(LargeMeteorPoints[LargeMeteorLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(LargeMeteorPoints[LargeMeteorLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(LargeMeteorPoints[LargeMeteorLines[i][1]], mTransform).Y + 480,
						(Color){255,255,255,255});
		}
		break;
	}
	default: {
		for (int i = 0; i < 4; i++) {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(ErrorMeteorPoints[ErrorMeteorLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(ErrorMeteorPoints[ErrorMeteorLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(ErrorMeteorPoints[ErrorMeteorLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(ErrorMeteorPoints[ErrorMeteorLines[i][1]], mTransform).Y + 480,
						(Color){255,255,255,255});
		}

	}
	}
}

/*void Meteor::DrawDebugMisc() {
	mDebugShowSize[0] = MeteorSize + '0';
	DrawText(mDebugShowSize, MeteorLocation.X, 480 - MeteorLocation.Y, 20, (Color){255, 255, 255, 255});
}*/

//Pointless function
