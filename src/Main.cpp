/*
 * Main.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: NMc
 */

#include "RLZen/RLZenCore.h"
#ifdef _WIN32
#include <windows.h>
#endif

#include "ZenAsteroid/ZenAsteroidApp.h"

#ifdef _WIN32
int WINAPI WinMain	(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nShowCmd) {
#else
int main (int argc, char** argv) {
#endif
	if (RLZenCore::Init()) {
		ZenAsteroidApp::Run();
		ZenAsteroidApp::Close();
		return 0;
	} else {
		return 1;
	}
}
