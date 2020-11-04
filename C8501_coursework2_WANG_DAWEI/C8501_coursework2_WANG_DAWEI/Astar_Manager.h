#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include <algorithm>

#include "Astar_Grid.h"
#include "Unit.h"

namespace maze2 {
	class Astar_Manager
	{
	private:
		std::vector<std::vector<maze2::Unit*>> m_grids;
		std::vector<Astar_Grid*> m_openList;
		std::vector<Astar_Grid*> m_closeList;

		std::pair<int, int> m_mapScale;

		//find path by grids' parent
		void generatePath(Astar_Grid* grid);

		//collect grids which can be a path around a grid
		std::vector<Astar_Grid*> selectAroundGrid(Astar_Grid* grid);

		//calculate Manhattan Distance
		int calculManhattanDis(Astar_Grid* cur, Astar_Grid* target);
		int calculManhattanDis(const std::pair<int, int>& cur, const std::pair<int, int>& target);

		//judge is grid in open list
		bool isGridInOpenList(Astar_Grid* target);

		//sort open list, bubble sort
		void updateOpenList();

		//remove element from open list
		void removeElementFromOpenList(Astar_Grid* target);
	public:
		Astar_Manager(const std::vector<std::vector<maze2::Unit*>>& units,const std::pair<int, int>& mapScale);
		~Astar_Manager();

		//core function of A star path finding
		bool findPath(const std::pair<int, int>& origin, const std::pair<int, int>& target);
	};
}
