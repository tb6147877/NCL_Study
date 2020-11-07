#include "Unit.h"

//Unit is a point on the map, x is its row number, y is its column number
//type is itself type, mapType is a type in the map
maze2::Unit::Unit(const int x, const int y, const UnitType type, const MapType mapType) 
	:m_x{ x }, m_y{ y }, m_type{ type }, m_mapType{mapType}{}

maze2::Unit::~Unit() {}

void maze2::Unit::draw(const bool isDrawPath,  const bool isDrawPlayer) {
	if (isDrawPlayer)
	{
		maze2::Tools::coloredCout("P", Tools::FColor::F_Yellow);
		return;
	}
	switch (m_type)
	{
	case UnitType::SPACE:
		std::cout << " ";
		break;
	case UnitType::ORIGIN:
		maze2::Tools::coloredCout("F", Tools::FColor::F_Red);
		break;
	case UnitType::WALL:
		maze2::Tools::coloredCout("X", Tools::FColor::F_Cyan);
		break;
	case UnitType::EXIT:
		maze2::Tools::coloredCout("E", Tools::FColor::F_Blue);
		break;
	case UnitType::PATH:
		if (isDrawPath)
		{
			maze2::Tools::coloredCout("o", Tools::FColor::F_Green);
		}
		else {
			std::cout << " ";
		}
		break;
	}
}

std::pair<int, int> maze2::Unit::getCoordinate() {
	return std::pair<int, int>{m_x, m_y};
}

char maze2::Unit::getGraphic() {
	switch (m_type)
	{
	case UnitType::SPACE:
		return ' ';
	case UnitType::ORIGIN:
		return 'F';
	case UnitType::WALL:
		return 'X';
	case UnitType::EXIT:
		return 'E';
	case UnitType::PATH:
		return 'o';
	}
}