/*
 * Ship.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#include "Ship.h"

#include <iostream>
#include <math.h>
#include <vector>
#include "raylib.h"

#include "Bullet.h"
#include "Framework/MathUtilities.h"
#include "Meteor.h"
#include "MeteorFragment.h"

Ship::Ship() = default;

Ship::Ship(Vector2f InitPosition, short InitHealth) {
	ShipLocation = InitPosition;
	ShipHealth = InitHealth;
}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

float ShipAcceleration = 64.0;
float ShipDeceleration = 96.0;
float ShipSpinSpeed = 3.0;

extern std::vector<Bullet> gBullets;
extern std::vector<Meteor> meteor;
extern std::vector<MeteorFragment> gMeteorFragments;
//extern std::vector<Ship> ship;

float ShipScale = 13.5;

Vector2f TransformedColliders[4];

void Ship::ControlShip() {
	ShipVelocity.X += sinf(ShipRotation) * ShipAcceleration * GetFrameTime() * (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
	ShipVelocity.Y += cosf(ShipRotation) * ShipAcceleration * GetFrameTime() * (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
	ShipRotation -= ShipSpinSpeed * GetFrameTime() * (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
	ShipRotation += ShipSpinSpeed * GetFrameTime() * (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT));
	if (IsKeyPressed(KEY_SPACE) && mIsInvincible == false) {
		gBullets.push_back({(Vector2f){ShipLocation.X,ShipLocation.Y}, (Vector2f){sinf(ShipRotation), cosf(ShipRotation)}});
	}
}

void Ship::UpdateShip() {
	ShipLocation.X += ShipVelocity.X * GetFrameTime();
	ShipLocation.Y += ShipVelocity.Y * GetFrameTime();
	ShipLocation.X = fmodf(ShipLocation.X + 640, 640);
	ShipLocation.Y = fmodf(ShipLocation.Y + 480, 480);
	mTransform = MathUtilities::SRT2DToMatrix3f((Vector2f){ShipScale, ShipScale}, ShipRotation, (Vector2f){ShipLocation.X, ShipLocation.Y});
	mInvincibilityTimer -= GetFrameTime() * (mInvincibilityTimer > 0);
	//ShipRotation += GetFrameTime();
	//std::cout << GetFrameTime()-0.0166666675359011 << std::endl;
	for (int i = 0; i < 4; i++) {
		TransformedColliders[i].X = (mCollision[i].mLocation.X * cosf(ShipRotation)) + (mCollision[i].mLocation.Y * sinf(ShipRotation));
		TransformedColliders[i].Y = (mCollision[i].mLocation.X * -sinf(ShipRotation)) + (mCollision[i].mLocation.Y * cosf(ShipRotation));
	}
	if (mCollision[0].mDrawTest) {
		for (int i = 0; i < 4; i++) {
			DrawCircle(	ShipLocation.X + (TransformedColliders[i].X * ShipScale),
						480 - (ShipLocation.Y + (TransformedColliders[i].Y * ShipScale)),
						mCollision[i].mRadius * ShipScale,
						(Color){0, 170, 0, 255});
		}
	}
	if (Ship::CheckCollisions()) {
		if (!mIsInvincible) {
			ShipHealth--;
			mInvincibilityTimer = 1.0;
			mIsInvincible = true;
			for (unsigned int i = 0; i < 3; i++) {
				gMeteorFragments.push_back({(Vector2f){ShipLocation.X , ShipLocation.Y}});
			}
		}
	} else if (mInvincibilityTimer <= 0) {
		mIsInvincible = false;
	}
}

bool Ship::CheckCollisions() {
	for (unsigned int m = 0; m < meteor.size(); m++) {
		for (unsigned int s = 0; s < 4; s++) {
			float xDistanceFromMeteor = ShipLocation.X + (TransformedColliders[s].X * ShipScale) - meteor[m].MeteorLocation.X;
			float yDistanceFromMeteor = ShipLocation.Y + (TransformedColliders[s].Y * ShipScale) - meteor[m].MeteorLocation.Y;
			float SumOfColliderRadii = mCollision[s].mRadius * ShipScale + meteor[m].mCollision.mRadius * meteor[m].mCurrentScale;
			if ((xDistanceFromMeteor * xDistanceFromMeteor) + (yDistanceFromMeteor * yDistanceFromMeteor) < (SumOfColliderRadii * SumOfColliderRadii)) {
				return true;
			}
		}
	}
	return false;
}

const int ShipPointCount = 4;
/*Vector2f ShipPoints[ShipPointCount] = 	{(Vector2f){0.0 , 1.0},
							 (Vector2f){0.7071067811865475 , -0.7071067811865475},
							 //(Vector2f){0.0 , -0.382683432365},
							 (Vector2f){0.0 , -0.25},
							 (Vector2f){-0.7071067811865475 , -0.7071067811865475}};*/
Vector2f ShipPoints[ShipPointCount] = 	{(Vector2f){0.0 , 1.0},
							 (Vector2f){0.875 , -1.0},
							 (Vector2f){0.0 , -0.5},
							 (Vector2f){-0.875 , -1.0}};
int ShipLines[ShipPointCount][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};


void Ship::DrawShip() {
	for (int i = 0; i < ShipPointCount; i++) {
		switch (mIsInvincible) {
		case 1: {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][1]], mTransform).Y + 480,
						(Color){255,0,0,255});
			break;
		}
		default: {
			DrawLine(	MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][0]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][0]], mTransform).Y + 480,
						MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][1]], mTransform).X,
						-MathUtilities::Apply2DTransformToVector2f(ShipPoints[ShipLines[i][1]], mTransform).Y + 480,
						(Color){255,255,255,255});
		}
		}
	}
}
