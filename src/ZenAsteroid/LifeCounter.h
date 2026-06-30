/*
 * LifeCounter.h
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#ifndef ZENASTEROID_LIFECOUNTER_H_
#define ZENASTEROID_LIFECOUNTER_H_

#include "Framework/MathUtilities.h"

class LifeCounter {
public:
	LifeCounter();

	enum LifeCounterJustify {
		Left = false,
		Right = true
	};

	Vector2f mLocation = (Vector2f){100, 100};
	bool mJustify = LifeCounterJustify::Right;

	LifeCounter(Vector2f iLocation, bool iJustify);
	virtual ~LifeCounter();

	void Draw();
};

#endif /* ZENASTEROID_LIFECOUNTER_H_ */
