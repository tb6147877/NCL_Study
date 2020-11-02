#include "Astar_Grid.h"

maze1::Astar_Grid::Astar_Grid(Unit* unit) 
	:m_unit{ unit }, m_parent{ nullptr }, m_f_value{ 0 }, m_g_value{ 0 }, m_h_value{ 0 }
{

}


maze1::Astar_Grid::~Astar_Grid() {

}


