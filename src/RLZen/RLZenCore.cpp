/*
 * RLZenCore.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#include "RLZenCore.h"

#include "raylib.h"

RLZenCore::RLZenCore() {
	// TODO Auto-generated constructor stub

}

RLZenCore::~RLZenCore() {
	// TODO Auto-generated destructor stub
}

bool RLZenCore::Init() {
	InitAudioDevice();
	return true;
}
