#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <functional>

#include "Unit.h"
#include "Tools.h"
#include "MazeConfig.h"

namespace maze1 {

	class Map
	{
	private:
		//maze1::Unit* m_units[];
		std::vector<std::vector<maze1::Unit*>> m_units;
		int m_row;
		int m_column;
		int m_exitNum;
		int m_centerX;
		int m_centerY;

		Unit::MapType judgeMapType(const int x, const int y);
		Unit::UnitType randomUnitType();
		Unit* generateUnit(const int x, const int y);
		Unit* generateUnit(const int x, const int y,const Unit::UnitType type, const Unit::MapType mapType);
		void initMap();
		void walkMap(const std::function<void(Unit* unit, Map* map)>& func);
		void setExit();
	public:
		Map(const int row, const int column,const int exitNum);
		~Map();
		int getExitNumber() { return m_exitNum; }
		bool checkHasPath();
		void draw();
	};

}