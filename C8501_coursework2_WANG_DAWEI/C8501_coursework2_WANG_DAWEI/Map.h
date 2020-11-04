#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <utility>
#include <string>

#include "Unit.h"
#include "Tools.h"
#include "MazeConfig.h"
#include "Astar_Manager.h"


namespace maze2 {
	//map stores all the units and provides some related functions
	class Map
	{
	private:
		std::vector<std::vector<maze2::Unit*>> m_units;
		int m_row;
		int m_column;
		int m_exitNum;
		int m_centerX;
		int m_centerY;

		int m_generateTimes;
		std::vector<Unit*> m_exits;

		//decide what a MapType it is of a position on the map
		Unit::MapType judgeMapType(const int x, const int y);

		//random a UnitType
		Unit::UnitType randomUnitType();

		//generate a unit 
		Unit* generateUnit(const int x, const int y);

		//actually generate a unit 
		Unit* generateUnit(const int x, const int y,const Unit::UnitType type, const Unit::MapType mapType);

		//generate the whole map
		void initMap();

		//go through every unit on the map and excute the function
		//para:a function pointer
		void walkMap(const std::function<void(Unit* unit, Map* map)>& func);

		//set exits on the map
		void setExit();

		//if the map don't have a path, this function is needed
		void reduceWall();

		//in the map, there is 4 points cannot be an exit because they can lead to no path, there are 4 corners
		bool isBlindUnit(Unit* unit);
	public:
		Map(const int row, const int column,const int exitNum);
		Map() = default;
		~Map();

		int getExitNumber() { return m_exitNum; }
		std::vector<std::vector<maze2::Unit*>> getUnits() { return m_units; }
		std::pair<int, int> getMapScale() { return std::pair<int, int>{m_row, m_column}; }
		std::pair<int, int> getCenter() { return std::pair<int, int>{m_centerX, m_centerY}; }
		std::vector<Unit*> getExits() { return m_exits; }

		//check wether this map has a path
		//para::arr stores exits which have find path
		bool checkHasPath(std::vector<Unit*>& arr);

		//draw the whole map
		//para:if isDrawPath equals true, path symbol 'o' will be draw; otherwise draw space symbol ' '
		void draw(const bool isDrawPath=true);

		//save map to disk
		void serialize(const std::string& path);

		//read file from disk
		void unserialize(const std::string& path);
	};

}