/*
 * LifeCounter.cpp
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#include "LifeCounter.h"

#include <vector>
#include "raylib.h"

#include "Ship.h"

LifeCounter::LifeCounter() = default;

LifeCounter::LifeCounter(Vector2f iLocation, bool iJustify) {
	mLocation = iLocation;
	mJustify = iJustify;
}

LifeCounter::~LifeCounter() {
	// TODO Auto-generated destructor stub
}

extern std::vector<Ship> ship;

float lcShipScale = 8.0;

const int lcShipPointCount = 4;
Vector2f lcShipPoints[lcShipPointCount] = 	{(Vector2f){0.0 , 1.0},
							 (Vector2f){0.875 , -1.0},
							 (Vector2f){0.0 , -0.5},
							 (Vector2f){-0.875 , -1.0}};
int lcShipLines[lcShipPointCount][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};

void LifeCounter::Draw() {
	for (int lc = 0; lc < ship[0].ShipHealth; lc++) {
		for (int i = 0; i < lcShipPointCount; i++) {
			DrawLine(lcShipPoints[lcShipLines[i][0]].X * lcShipScale + mLocation.X - (lc * 20), -lcShipPoints[lcShipLines[i][0]].Y * lcShipScale + mLocation.Y,
					lcShipPoints[lcShipLines[i][1]].X * lcShipScale + mLocation.X - (lc * 20), -lcShipPoints[lcShipLines[i][1]].Y * lcShipScale + mLocation.Y,
					(Color){255,255,255,255});
		}
	}
}
