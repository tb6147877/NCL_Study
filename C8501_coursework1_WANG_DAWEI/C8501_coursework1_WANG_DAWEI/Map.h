#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <utility>
#include <windows.h>
#include <string>

#include "Unit.h"
#include "Tools.h"
#include "MazeConfig.h"
#include "Astar_Manager.h"


namespace maze1 {
	class Astar_manager;
	class Map
	{
	private:
		std::vector<std::vector<maze1::Unit*>> m_units;
		int m_row;
		int m_column;
		int m_exitNum;
		int m_centerX;
		int m_centerY;

		int m_generateTimes;
		std::vector<Unit*> m_exits;
		Unit::MapType judgeMapType(const int x, const int y);
		Unit::UnitType randomUnitType();
		Unit* generateUnit(const int x, const int y);
		Unit* generateUnit(const int x, const int y,const Unit::UnitType type, const Unit::MapType mapType);
		void initMap();
		void walkMap(const std::function<void(Unit* unit, Map* map)>& func);
		void setExit();
		void reduceWall();
		bool isBlindUnit(Unit* unit);
	public:
		Map(const int row, const int column,const int exitNum);
		Map() = default;
		~Map();

		int getExitNumber() { return m_exitNum; }
		std::vector<std::vector<maze1::Unit*>> getUnits() { return m_units; }
		std::pair<int, int> getMapScale() { return std::pair<int, int>{m_row, m_column}; }
		std::pair<int, int> getCenter() { return std::pair<int, int>{m_centerX, m_centerY}; }
		std::vector<Unit*> getExits() { return m_exits; }
		bool checkHasPath(std::vector<Unit*>& arr);
		void draw(const bool isDrawPath=true);
		void serialize(const std::string& path);
		void unserialize(const std::string& path);
	};

}