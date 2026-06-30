/*
 * ScoreCounter.h
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_SCORECOUNTER_H_
#define ZENASTEROID_SCORECOUNTER_H_

#include "Framework/MathUtilities.h"

class ScoreCounter {
public:
	ScoreCounter();

	unsigned short mPlayerID = 0;
	Vector2f mLocation = (Vector2f){100, 100};

	ScoreCounter(Vector2f iLocation);
	virtual ~ScoreCounter();

	void Draw();
};

#endif /* ZENASTEROID_SCORECOUNTER_H_ */
