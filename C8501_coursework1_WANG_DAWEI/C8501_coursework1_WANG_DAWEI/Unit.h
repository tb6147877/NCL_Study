#pragma once

#include <iostream>
#include <utility>
#include <string>

#include "Tools.h"

namespace maze1 {
	//Unit is a point on the map
	class Unit
	{
	public:
		enum UnitType {
			SPACE,
			WALL,
			ORIGIN,
			EXIT,
			PATH
		};

		enum MapType {
			CENTER,
			CENTER_REGION,
			NORMAL,
			EDGE
		};

	private:
		int m_x;
		int m_y;
		UnitType m_type;
		MapType m_mapType;

	public:
		//Unit is a point on the map, x is its row number, y is its column number
		//type is itself type, mapType is a type in the map
		Unit(const int x, const int y, const UnitType type,const MapType mapType) ;
		~Unit();
		void setUnitType(const UnitType type) { m_type = type; }
		UnitType getUnitType() { return m_type; }
		MapType getMapType() { return m_mapType; }
		std::pair<int,int> getCoordinate();

		//show the unit on the screen
		void draw(const bool isDrawPath=true);
		char getGraphic();
	};
}

