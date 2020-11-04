#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#include "windows.h"
#include "shlobj.h"


namespace maze2 {
	static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	class Tools
	{
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
	};

}