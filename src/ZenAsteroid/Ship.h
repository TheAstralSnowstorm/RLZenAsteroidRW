/*
 * Ship.h
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_SHIP_H_
#define ZENASTEROID_SHIP_H_

#include "raylib.h"

#include "Framework/Collider.h"
#include "Framework/MathUtilities.h"

class Ship {
public:
	Ship();

	Vector2f ShipLocation = (Vector2f){320, 240};
	float ShipRotation = 0.0;
	Matrix3f mTransform;
	Vector2f ShipVelocity = (Vector2f){0, 0};
	short ShipHealth = 3;
	Collider mCollision[4] = {	(Collider){(Vector2f){0.0, 0.0}, 1.0},
								(Collider){(Vector2f){0.0, 1.0}, 0.5},
								(Collider){(Vector2f){-1.0, -1.0}, 0.5},
								(Collider){(Vector2f){1.0, -1.0}, 0.5}};
	unsigned int mScore = 0;
	bool mIsInvincible = true;
	float mInvincibilityTimer = 0.0;

	Ship(Vector2f InitPosition, short InitHealth);
	virtual ~Ship();

	void ControlShip();
	void UpdateShip();
	bool CheckCollisions();
	void DrawShip();
};

#endif /* ZENASTEROID_SHIP_H_ */
