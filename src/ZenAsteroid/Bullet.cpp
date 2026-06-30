/*
 * Bullet.cpp
 *
 *  Created on: Apr 22, 2026
 *      Author: NMc
 */

#include "Bullet.h"

#include "raylib.h"

#include "Framework/MathUtilities.h"

Bullet::Bullet() = default;

Bullet::Bullet(Vector2f iLocation, Vector2f iVelocity) {
	mLocation = iLocation;
	mVelocity = iVelocity;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

float BulletSpeedAmplifier = 320.0;

const int BulletPointCount = 4;
Vector2f BulletPoints[BulletPointCount] = {(Vector2f){-1.0 , -1.0}, (Vector2f){1.0 , -1.0}, (Vector2f){-1.0 , 1.0}, (Vector2f){1.0 , 1.0}};
const int BulletLineCount = 6;
int BulletLines[BulletLineCount][2] = {{0, 1}, {1, 3}, {3, 2}, {2, 0}, {0, 3}, {1, 2}};


void Bullet::Update() {
	mLocation.X += mVelocity.X * BulletSpeedAmplifier * GetFrameTime();
	mLocation.Y += mVelocity.Y * BulletSpeedAmplifier * GetFrameTime();
	mTimer -= GetFrameTime();
	if (mCollision.mDrawTest) {
		DrawCircle(	mLocation.X, 480 - mLocation.Y, mCollision.mRadius * mScale, (Color){0, 170, 0, 255});
	}
	Bullet::Draw();
}

void Bullet::Draw() {
	for (int i = 0; i < BulletLineCount; i++) {
		DrawLine(BulletPoints[BulletLines[i][0]].X * mScale + mLocation.X, BulletPoints[BulletLines[i][0]].Y * mScale  - mLocation.Y + 480,
				BulletPoints[BulletLines[i][1]].X * mScale  + mLocation.X, BulletPoints[BulletLines[i][1]].Y * mScale  - mLocation.Y + 480,
				(Color){255,255,255,255});
	}
}
