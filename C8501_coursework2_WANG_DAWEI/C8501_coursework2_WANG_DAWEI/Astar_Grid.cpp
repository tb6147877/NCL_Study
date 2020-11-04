#include "Astar_Grid.h"

maze2::Astar_Grid::Astar_Grid(const int x, const int y, const UnitType type, const MapType mapType) 
	: Unit{x,y,type,mapType}, m_parent{ nullptr }, m_f_value{ 0 }, m_g_value{ 0 }, m_h_value{ 0 }
{

}


maze2::Astar_Grid::~Astar_Grid() {

}


