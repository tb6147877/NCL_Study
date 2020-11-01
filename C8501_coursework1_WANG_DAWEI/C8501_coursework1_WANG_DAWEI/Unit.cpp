#include "Unit.h"

maze1::Unit::Unit(const int x, const int y, const UnitType type, const MapType mapType) 
	:m_x{ x }, m_y{ y }, m_type{ type }, m_mapType{mapType}{}

maze1::Unit::~Unit() {}

void maze1::Unit::draw() {
	switch (m_type)
	{
	case UnitType::SPACE:
		std::cout << " ";
		break;
	case UnitType::ORIGIN:
		std::cout << "S";
		break;
	case UnitType::WALL:
		std::cout << "X";
		break;
	case UnitType::EXIT:
		std::cout << "E";
		break;
	case UnitType::PATH:
		std::cout << "o";
		break;
	}
}

std::pair<int, int> maze1::Unit::getCoordinate() {
	return std::pair<int, int>{m_x, m_y};
}