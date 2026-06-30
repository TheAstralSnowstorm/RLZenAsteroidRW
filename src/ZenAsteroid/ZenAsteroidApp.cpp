/*
 * TestApp.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#include "ZenAsteroidApp.h"

#include "raylib.h"
#include <vector>

#include "Bullet.h"
#include "Framework/RNGUtilities.h"
#include "LifeCounter.h"
#include "Meteor.h"
#include "MeteorFragment.h"
#include "ScoreCounter.h"
#include "Ship.h"

ZenAsteroidApp::ZenAsteroidApp() {
	// TODO Auto-generated constructor stub

}

ZenAsteroidApp::~ZenAsteroidApp() {
	// TODO Auto-generated destructor stub
}

unsigned int Level = 0;

std::vector<Bullet> gBullets;
std::vector<Meteor> meteor;
std::vector<MeteorFragment> gMeteorFragments;
std::vector<Ship> ship;

ScoreCounter shipScore = (ScoreCounter){(Vector2f){32, 432}};
LifeCounter shipLives = (LifeCounter){(Vector2f){600, 440}, true};

void ZenAsteroidApp::Run() {
	InitWindow(640, 480, "RLZenAsteroid by NMc/AstralSnowstorm");
	SetTargetFPS(60);

	//gBullets.push_back({(Vector2f){320,240}, (Vector2f){1,1}});
	ship.push_back({(Vector2f){320,240}, 3});
	//ship.push_back({(Vector2f){280,200}, 1});

	while (!WindowShouldClose()) {
		BeginDrawing();
		BeginBlendMode(BLEND_ADDITIVE);
		ClearBackground((Color){0,0,0,255});

		for (unsigned int b = 0; b < gBullets.size(); b++) {
			if (gBullets[b].mTimer <= 0) {
				gBullets.erase(gBullets.begin() + b);
			}
			gBullets[b].Update();
		}

		if (meteor.size() == 0) {
			Level++;
			for (unsigned int sl = 0; sl < ship.size(); sl++) {
				ship[sl].mIsInvincible = true;
				if (Level % 3 == 0) {
					ship[sl].ShipHealth += 1;
				}
			}
			for (unsigned int cnm = 0; cnm < Level + 2; cnm++) {
				meteor.push_back({	(Vector2f){RNGUtilities::whRandom(0.0, 640.0), RNGUtilities::whRandom(0.0, 480.0)},
									RNGUtilities::whRandom(-3.1415926535897932384626433832795, 3.1415926535897932384626433832795),
									(Vector2f){RNGUtilities::whRandom(-64.0, 64.0), RNGUtilities::whRandom(-64.0, 64.0)},
									RNGUtilities::whRandom(-3.1415926535897932384626433832795, 3.1415926535897932384626433832795), 3});
			}
		}
		for (unsigned int m = 0; m < meteor.size(); m++) {
			// TODO If bugs occur, make sure to scrutinize this particular code.
			if (meteor[m].Meteor::CheckCollisions()) {
				meteor.erase(meteor.begin() + m);
			}
			meteor[m].DrawMeteor();
			meteor[m].UpdateMeteor();
		}

		for (unsigned int mf = 0; mf < gMeteorFragments.size(); mf++) {
			if (gMeteorFragments[mf].mScale < 0) {
				gMeteorFragments.erase(gMeteorFragments.begin() + mf);
			}
			gMeteorFragments[mf].Update();
		}

		for (unsigned int s = 0; s < ship.size(); s++) {
			if (ship[s].ShipHealth < 1) {
				for (unsigned int i = 0; i < 9; i++) {
					gMeteorFragments.push_back({(Vector2f){ship[s].ShipLocation.X , ship[s].ShipLocation.Y}});
				}
				ship.erase(ship.begin() + s);
			}
			ship[s].DrawShip();
			ship[s].ControlShip();
			ship[s].UpdateShip();
		}

		shipScore.Draw();
		shipLives.Draw();

		EndBlendMode();
		EndDrawing();
	}
}

void ZenAsteroidApp::Close() {
	gBullets.clear();
	meteor.clear();
	gMeteorFragments.clear();
	ship.clear();
	CloseAudioDevice();
	CloseWindow();
}
