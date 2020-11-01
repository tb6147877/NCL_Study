#pragma once

#include <iostream>
#include <utility>

namespace maze1 {
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
		Unit(const int x, const int y, const UnitType type,const MapType mapType) ;
		~Unit();
		void setUnitType(const UnitType type) { m_type = type; }
		UnitType getUnitType() { return m_type; }
		MapType getMapType() { return m_mapType; }
		std::pair<int,int> getCoordinate();
		void draw();
	};
}

