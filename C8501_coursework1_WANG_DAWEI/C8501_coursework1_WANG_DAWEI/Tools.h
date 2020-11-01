#pragma once

#include <iostream>
#include <random>
#include <ctime>

namespace maze1 {
	static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	class Tools
	{
	private:
	public:
		static int getRamdom(int min,int max);
	};

}