//C++ includes
#include <stdio.h>
#include <string>
#include <iostream>

//Other includes
#include "Game.h"
#include "AllegroSettings.h"

using namespace std;

Game::Game(int width, int height, string values[15]) {
	widthOfBoard = width;
	heightOfBoard = height;
	for (int i = 0; i < 15; i++) {
		initValues[i] = values[i];
	}
}

void Game::generate() {
	cout << "Game of size " << widthOfBoard << "x" << heightOfBoard << " is being generated" << endl;
}

void Game::run() {
	cout << "Game is running" << endl;
	for (int i = 0; i < 15; i++) {
		cout << "\tParameter " << i << ": " << initValues[i] << endl;
	}
}