/*
 * ScoreCounter.cpp
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#include "ScoreCounter.h"

//#include <cstring>
#include <iostream>
#include <vector>
#include "raylib.h"

#include "Ship.h"

ScoreCounter::ScoreCounter() = default;

ScoreCounter::ScoreCounter(Vector2f iLocation) {
	mLocation = iLocation;
}

ScoreCounter::~ScoreCounter() {
	// TODO Auto-generated destructor stub
}

extern std::vector<Ship> ship;

char StringScore[11];

void ScoreCounter::Draw() {
	unsigned int t0 = ship[0].mScore;
	for (unsigned int i = 0; i < 10; i++) {
		StringScore[9-i] = (t0 % 10) + '0';
		t0 /= 10;
	}
	DrawText(StringScore, mLocation.X, mLocation.Y, 20, (Color){255, 255, 255, 255});
	//std::cout << StringScore << std::endl;
}
