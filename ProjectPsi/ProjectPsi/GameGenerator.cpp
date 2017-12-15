//
// Made by Bryton Leason for project Psi
//

//C++ includes
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

//Other includes
#include "GameGenerator.h"
#include "AllegroSettings.h"

using namespace std;

GameGenerator::GameGenerator(int width, int height, string values[15]) {
    widthOfBoard = width;
    heightOfBoard = height;
    for (int i = 0; i < 15; i++) {
        initValues[i] = values[i];
    }
}

void GameGenerator::generate() {
    cout << "Game of size " << widthOfBoard << "x" << heightOfBoard << " is being generated" << endl;
    gameBoard.resize(heightOfBoard);
	rgbGameBoard.resize(heightOfBoard);
    for (int i = 0; i < heightOfBoard; i++) {
        gameBoard[i].resize(widthOfBoard);
		rgbGameBoard[i].resize(widthOfBoard);
    }
    generateSand();
    generateSnow();
    generateForest();
    generateJungle();
    generateRivers();
    generateOceans();
    smooth();
	populateRgbMap();
	writeBitMap();
	cout << "\tBoard is generated!" << endl;
}

void GameGenerator::generateSand()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 0;
        }
    }
}

void GameGenerator::generateSnow()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 1;
        }
    }
}

void GameGenerator::generateForest()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 2;
        }
    }
}

void GameGenerator::generateJungle()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 3;
        }
    }
}

void GameGenerator::generateRivers()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = -1;
        }
    }
}

void GameGenerator::generateOceans()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = -2;
        }
    }
}

void GameGenerator::smooth()
{
    for (int height = 0; height < heightOfBoard; height++) {
        for (int width = 0; width < widthOfBoard; width++) {
            gameBoard[height][width] = 0;
        }
    }
}

void GameGenerator::populateRgbMap()
{
	for (int height = 0; height < heightOfBoard; height++) {
		for (int width = 0; width < widthOfBoard; width++) {
			rgbGameBoard[height][width] = rgbLookupMap.at(gameBoard[height][width]);
		}
	}

}

void GameGenerator::printMapToFile()
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

}void GameGenerator::printRgbMapToFile()
{
	cout << "Writing map to file" << endl;
	time_t currentTimeSinceEpoch = std::time(nullptr);
	stringstream streamForString;
	streamForString << currentTimeSinceEpoch;
	ofstream mapFile;
	string fileNameString = "generatedMapAsRgbValues_" + streamForString.str() + ".txt";
	cout << "\tMap File will be named " << fileNameString << endl;
	for (int height = 0; height < heightOfBoard; height++) {
		for (int width = 0; width < widthOfBoard; width++) {
			tuple<int, int, int> cachedValue = rgbGameBoard[height][width];
			mapFile << "(" << get<0>(cachedValue) << ", " << get<1>(cachedValue) << ", " << get<2>(cachedValue) << ") ";
		}
		mapFile << "\n";
	}
	mapFile.close();
	cout << "\tNote: this file pretty much can't be viewed" << endl;
	cout << "\tDone generation!" << endl;
}

void GameGenerator::writeBitMap()
{
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;

	//Defining the file header
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfSize = 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + widthOfBoard * heightOfBoard * 3;
	bitmapFileHeader.bfOffBits = 0x36;

	//Defining the info header
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = widthOfBoard;
	bitmapInfoHeader.biHeight = heightOfBoard;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = 0;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 5000;
	bitmapInfoHeader.biYPelsPerMeter = 5000;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	FILE * bitMap;
	cout << "\tBitMap be named " << "bitMapToUse.bmp" << endl;
	bitMap = fopen("bitMapToUse.bmp", "w");

	//This writes the headers
	fwrite(&bitmapFileHeader, 1, sizeof(bitmapFileHeader), bitMap);
	fwrite(&bitmapInfoHeader, 1, sizeof(bitmapInfoHeader), bitMap);

	//This writes the bitmap
	//Note: bitmaps are BGR not RGB
	for (int height = 0; height < heightOfBoard; height++) {
		for (int width = 0; width < widthOfBoard; width++) {
			tuple<int, int, int> cachedValue = rgbGameBoard[height][width];
			unsigned char red = get<0>(cachedValue);
			unsigned char green = get<1>(cachedValue);
			unsigned char blue = get<2>(cachedValue);
			fwrite(&blue, 1, 1, bitMap);
			fwrite(&green, 1, 1, bitMap);
			fwrite(&red, 1, 1, bitMap);
		}
	}
	fclose(bitMap);
}
