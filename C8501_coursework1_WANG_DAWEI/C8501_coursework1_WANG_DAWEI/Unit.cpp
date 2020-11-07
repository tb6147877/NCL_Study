#include "Unit.h"

#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define CYAN "\033[36m" /* Cyan */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */

//Unit is a point on the map, x is its row number, y is its column number
//type is itself type, mapType is a type in the map
maze1::Unit::Unit(const int x, const int y, const UnitType type, const MapType mapType) 
	:m_x{ x }, m_y{ y }, m_type{ type }, m_mapType{mapType}{}

maze1::Unit::~Unit() {}

void maze1::Unit::draw(const bool isDrawPath) {
	switch (m_type)
	{
	case UnitType::SPACE:
		std::cout << " ";
		break;
	case UnitType::ORIGIN:
		maze1::Tools::coloredCout("S", Tools::FColor::F_Red);
		break;
	case UnitType::WALL:
		maze1::Tools::coloredCout("X", Tools::FColor::F_Cyan);
		break;
	case UnitType::EXIT:
		maze1::Tools::coloredCout("E", Tools::FColor::F_Yellow);
		break;
	case UnitType::PATH:
		if (isDrawPath)
		{
			maze1::Tools::coloredCout("o", Tools::FColor::F_Green);
		}
		else {
			std::cout << " ";
		}
		
		break;
	}
}

std::pair<int, int> maze1::Unit::getCoordinate() {
	return std::pair<int, int>{m_x, m_y};
}

char maze1::Unit::getGraphic() {
	switch (m_type)
	{
	case UnitType::SPACE:
		return ' ';
	case UnitType::ORIGIN:
		return 'S';
	case UnitType::WALL:
		return 'X';
	case UnitType::EXIT:
		return 'E';
	case UnitType::PATH:
		return 'o';
	}
}