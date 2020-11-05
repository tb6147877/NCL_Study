#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Map.h"


namespace maze2 {
	class MapBuilder
	{
	private:
		static std::vector<Unit*> analysisOneLine(const std::string& str, const int row);
	public:
		static Map buildMap(const std::string& path);
	};

}