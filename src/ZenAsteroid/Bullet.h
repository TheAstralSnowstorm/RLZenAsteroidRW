/*
 * Bullet.h
 *
 *  Created on: Apr 22, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_BULLET_H_
#define ZENASTEROID_BULLET_H_

#include "Framework/Collider.h"
#include "Framework/MathUtilities.h"

class Bullet {
public:
	Bullet();

	Vector2f mLocation = (Vector2f){320, 240};
	Vector2f mVelocity = (Vector2f){0, 1};
	Collider mCollision = (Collider){(Vector2f){0.0, 0.0}, 1.2732395447351626861510701069801};
	float mTimer = 1.5;

	Bullet(Vector2f iLocation, Vector2f iVelocity);
	virtual ~Bullet();

	float mScale = 1.0;

	void Update();
	void Draw();
};

#endif /* ZENASTEROID_BULLET_H_ */
