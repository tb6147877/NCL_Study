#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#include "windows.h"
#include "shlobj.h"


namespace maze1 {
	static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	class Tools
	{
	public:
		enum FColor
		{
			F_Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
			F_Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
			F_Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
			F_Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
			F_Purple = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
			F_Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
			F_Gray = FOREGROUND_INTENSITY,
			F_White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			F_HighWhite = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			F_Black = 0,
		};

		enum BColor
		{
			B_Red = BACKGROUND_INTENSITY | BACKGROUND_RED,
			B_Green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
			B_Blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
			B_Yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
			B_Purple = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
			B_Cyan = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
			B_White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
			B_HighWhite = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
			B_Black = 0,
		};
	private:
	public:
		//get a random number, include min and max
		static int getRamdom(int min,int max);

		//read a file by line, and set the row number and column number of the content
		//return:every line of content is a string stores in a vector
		static std::vector<std::string> readFile(const std::string& path, int& row, int& column);

		//write content to a specific path
		static void writeFile(const std::string& content, const std::string& path);

		//check wether this path has a file
		static bool hasFile(const std::string& path);

		//get windows desktop path
		//return:the path
		static std::string getDesktopPath();

		static void coloredCout(const std::string& str, FColor foreColor = F_White, BColor backColor = B_Black);
	};

}