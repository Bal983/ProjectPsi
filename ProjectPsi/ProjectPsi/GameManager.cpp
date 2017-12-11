//
// Made by Bryton Leason for project Psi
//

//Standard Includes
#include <stdio.h>
#include <iostream>

#include "GameManager.h"
#include "GraphicsSystem.h"

using namespace std;

GameManager::GameManager(GameGenerator* gen, GraphicsSystem* sys)
{
	gameGenerator = gen;
	graphicsSystem = sys;
}

void GameManager::handleControl()
{
	cout << "made it here!" << endl;
	graphicsSystem->handleGameControl();
}
