#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include <algorithm>

#include "Astar_Grid.h"
#include "Unit.h"

namespace maze1 {
	class Astar_Manager
	{
	private:
		std::vector<std::vector<maze1::Astar_Grid*>> m_grids;
		std::vector<Astar_Grid*> m_openList;
		std::vector<Astar_Grid*> m_closeList;

		std::pair<int, int> m_mapScale;
		std::vector<std::vector<maze1::Unit*>> m_units;

		void initGrids();
		void generatePath(Astar_Grid* grid);
		std::vector<Astar_Grid*> selectAroundGrid(Astar_Grid* grid);
		int calculManhattanDis(Astar_Grid* cur, Astar_Grid* target);
		int calculManhattanDis(const std::pair<int, int>& cur, const std::pair<int, int>& target);
		bool isGridInOpenList(Astar_Grid* target);
		void updateOpenList();
		void removeElementFromOpenList(Astar_Grid* target);
	public:
		Astar_Manager(const std::vector<std::vector<maze1::Unit*>>& units,const std::pair<int, int>& mapScale);
		~Astar_Manager();

		bool findPath(const std::pair<int, int>& origin, const std::pair<int, int>& target);
	};
}
