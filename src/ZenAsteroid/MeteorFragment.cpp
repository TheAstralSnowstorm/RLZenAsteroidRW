/*
 * MeteorFragment.cpp
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#include "MeteorFragment.h"

#include <math.h>
#include "raylib.h"

#include "Framework/RNGUtilities.h"

MeteorFragment::MeteorFragment() = default;

MeteorFragment::MeteorFragment(Vector2f iLocation) {
	mLocation = iLocation;
	mRotation = RNGUtilities::whRandom(-3.1415926535897932384626433832795, 3.1415926535897932384626433832795);
	mVelocity = (Vector2f){RNGUtilities::whRandom(-128.0, 128.0), RNGUtilities::whRandom(-128.0, 128.0)};
	mSpin = RNGUtilities::whRandom(-3.1415926535897932384626433832795, 3.1415926535897932384626433832795);
}

MeteorFragment::~MeteorFragment() {

}

const int MeteorFragmentPointCount = 3;
Vector2f MeteorFragmentPoints[MeteorFragmentPointCount] = {(Vector2f){0.0 , 1.0}, (Vector2f){1.0 , -0.5}, (Vector2f){-1.0 , -0.5}};
const int MeteorFragmentLineCount = 3;
int MeteorFragmentLines[MeteorFragmentLineCount][2] = {{0, 1}, {1, 2}, {2, 0}};

void MeteorFragment::Update() {
	mLocation.X += mVelocity.X * GetFrameTime();
	mLocation.Y += mVelocity.Y * GetFrameTime();
	mRotation += mSpin * GetFrameTime();
	mScale -= 4.0 * GetFrameTime();
	mTransform = MathUtilities::SRT2DToMatrix3f((Vector2f){mScale, mScale}, mRotation, (Vector2f){mLocation.X, mLocation.Y});
	MeteorFragment::Draw();
}

void MeteorFragment::Draw() {
	for (int i = 0; i < MeteorFragmentLineCount; i++) {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(MeteorFragmentPoints[MeteorFragmentLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(MeteorFragmentPoints[MeteorFragmentLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(MeteorFragmentPoints[MeteorFragmentLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(MeteorFragmentPoints[MeteorFragmentLines[i][1]], mTransform).Y + 480,
						(Color){255,255,255,255});
	}
}
