//
// Made by Bryton Leason for project Psi
//

#pragma once
#ifndef GAMEGENERATOR_HEADER
#define GAMEGENERATOR_HEADER
#include <vector>
#include <map>
#include <tuple>

class GameGenerator {
	private:
		int widthOfBoard;
		int heightOfBoard;
		std::string initValues[15];
		static std::map<int, std::tuple<int, int, int>> generateLookupMap() {
			std::map<int, std::tuple<int, int, int>> genMap;//Tuples are in R G B format
			genMap[-2] = std::make_tuple(0, 0, 255);//dark blue;
			genMap[-1] = std::make_tuple(30, 144, 255);//light blue;
			genMap[0] = std::make_tuple(194, 178, 128);//sand
			genMap[0] = std::make_tuple(255, 255, 250);//snow
			genMap[0] = std::make_tuple(0, 123, 12);//plains
			genMap[0] = std::make_tuple(34, 139, 34);//forest
			genMap[0] = std::make_tuple(41, 171, 135);//jungle
			return genMap;
		}
		std::map<int, std::tuple<int, int, int>> rgbLookupMap = generateLookupMap();
		std::vector<std::vector<int>> gameBoard;
		std::vector<std::vector<std::tuple<int, int, int>>> rgbGameBoard;
		void generateSand();
		void generateSnow();
		void generateForest();
		void generateJungle();
		void generateRivers();
		void generateOceans();
		void smooth();
		void populateRgbMap();
	public:
		GameGenerator(int, int, std::string values[15]);
		void generate();
		void printMapToFile();
		void printRgbMapToFile();
		void writeBitMap();
};
#endif