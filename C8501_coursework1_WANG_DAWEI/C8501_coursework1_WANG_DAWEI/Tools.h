#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>


namespace maze1 {
	static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	class Tools
	{
	private:
	public:
		static int getRamdom(int min,int max);
		static std::vector<std::string> readFile(const std::string& path, int& row, int& column);
		static void writeFile(const std::string& content, const std::string& path);
	};

}