/*
 * RNGUtilities.cpp
 *
 *  Created on: Apr 29, 2026
 *      Author: NMc
 */

#include "RNGUtilities.h"

#include <iostream>
#include <math.h>

unsigned int LFSRSeed = 1;
bool LFSRNewBit;

float whSeed1 = 100.0;
float whSeed2 = 100.0;
float whSeed3 = 100.0;

int RNGUtilities::zRandom() {
	int LFSROutput = 0;
	for (unsigned int i = 0; i < 32; i++) {
		LFSROutput = LFSROutput << 1;
		LFSRNewBit = (LFSRSeed ^ (LFSRSeed >> 7) ^ (LFSRSeed >> 15) ^ (LFSRSeed >> 25)) & 1;
		LFSRSeed = (LFSRSeed >> 1) | (LFSRNewBit << 31);
		LFSROutput = LFSROutput | LFSRNewBit;
	}
	//std::cout << LFSROutput << std::endl;
	return LFSROutput;
}

float RNGUtilities::whRandom(float Min, float Max) {
	float whOutput;
	whSeed1 = fmodf(171 * whSeed1, 30269);
	whSeed2 = fmodf(172 * whSeed2, 30307);
	whSeed3 = fmodf(170 * whSeed3, 30323);
	whOutput = fmodf(whSeed1 * 3.303710066404572e-5 + whSeed2 * 3.299567756623882e-5 + whSeed3 * 3.297826732183491e-5, 1.0);
	//std::cout << whOutput << std::endl;
	return whOutput * (Max - Min) + Min;
}
