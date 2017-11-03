//C++ includes
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

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
    gameBoard.resize(heightOfBoard);
    for (int i = 0; i < heightOfBoard; i++) {
        gameBoard[i].resize(widthOfBoard);
    }
    generateSand();
    generateSnow();
    generateForest();
    generateJungle();
    generateRivers();
    generateOceans();
    smooth();
}

void Game::generateSand()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 0;
        }
    }
}

void Game::generateSnow()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 1;
        }
    }
}

void Game::generateForest()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 2;
        }
    }
}

void Game::generateJungle()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 3;
        }
    }
}

void Game::generateRivers()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = -1;
        }
    }
}

void Game::generateOceans()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = -2;
        }
    }
}

void Game::smooth()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 0;
        }
    }
}

void Game::run() {
    cout << "Game is running" << endl;
    for (int i = 0; i < 15; i++) {
        cout << "\tParameter " << i << ": " << initValues[i] << endl;
    }
}

void Game::printMapToFile()
{
    cout << "Writing map to file" << endl;
    time_t currentTimeSinceEpoch = std::time(nullptr);
    stringstream streamForString;
    streamForString << currentTimeSinceEpoch;
    ofstream mapFile;
    string fileNameString = "generatedMapAsIntegers_" + streamForString.str() + ".txt";
    cout << "\tMap File will be named " << fileNameString << endl;
    mapFile.open(fileNameString);
    mapFile << "||===================================================||\n";
    mapFile << "||     Project Psi Exported Configuration Setting    ||\n";
    mapFile << "||   Created By Bryton Leason and Samual Horovatin   ||\n";
    mapFile << "||===================================================||\n";
    mapFile << "||                    Legend                         ||\n";
    mapFile << "||                  -2 = Deep Water                  ||\n"; 
    mapFile << "||                  -1 = Shallow Water               ||\n";
    mapFile << "||                   0 = Sand                        ||\n";
    mapFile << "||                   1 = Snow                        ||\n";
    mapFile << "||                   2 = Plains                      ||\n";
    mapFile << "||                   3 = Forest                      ||\n";
    mapFile << "||                   4 = Jungle                      ||\n";
    mapFile << "||===================================================||\n";
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            mapFile << gameBoard[height][width];
        }
        mapFile << "\n";
    }
    mapFile.close();
	cout << "\tNote: this file pretty much can't be viewed" << endl;
    cout << "\tDone generation!" << endl;
}
