#include "Astar_Manager.h"

//find path by grids' parent
void maze2::Astar_Manager::generatePath(Astar_Grid* grid) {
	if (grid->getParent()!=nullptr)
	{
		if (grid->getUnitType()!= Unit::UnitType::EXIT)
		{
			grid->setUnitType(Unit::UnitType::PATH);
		}
		generatePath(grid->getParent());
		m_path.push_back(grid);
	}
}

//collect grids which can be a path around a grid
std::vector<maze2::Astar_Grid*> maze2::Astar_Manager::selectAroundGrid(Astar_Grid* grid) {
	std::vector<maze2::Astar_Grid*> temp{};

	std::vector<std::pair<int,int>> grids{};
	//right
	int x1 = grid->getCoordinate().first+1;
	int y1 = grid->getCoordinate().second;
	grids.push_back(std::pair<int, int>{x1, y1});
	//left
	int x2 = grid->getCoordinate().first - 1;
	int y2 = grid->getCoordinate().second;
	grids.push_back(std::pair<int, int>{x2, y2});
	//up
	int x3 = grid->getCoordinate().first;
	int y3 = grid->getCoordinate().second+1;
	grids.push_back(std::pair<int, int>{x3, y3});
	//down
	int x4 = grid->getCoordinate().first;
	int y4 = grid->getCoordinate().second-1;
	grids.push_back(std::pair<int, int>{x4, y4});

	for (int i = 0; i < grids.size(); i++)
	{
		//out of map, skip
		if (grids[i].first < 0 or grids[i].second < 0
			or grids[i].first >= m_mapScale.first or grids[i].second >= m_mapScale.second)
		{
			continue;
		}

		//it is a wall, skip
		if (m_grids[grids[i].first][grids[i].second]->getUnitType() == Unit::UnitType::WALL)
		{
			continue;
		}

		//close list has contain this grid, skip
		if (std::find(m_closeList.begin(), m_closeList.end(), m_grids[grids[i].first][grids[i].second]) != m_closeList.end())
		{
			continue;
		}
		Unit* tempUnit = m_grids[grids[i].first][grids[i].second];
		temp.push_back(dynamic_cast<Astar_Grid*>(tempUnit));
	}
	return temp;
}

//calculate Manhattan Distance
int maze2::Astar_Manager::calculManhattanDis(Astar_Grid* cur, Astar_Grid* target) {
	return (abs(target->getCoordinate().first - cur->getCoordinate().first) + abs(target->getCoordinate().second - cur->getCoordinate().second)) * 10;
}

//calculate Manhattan Distance
int maze2::Astar_Manager::calculManhattanDis(const std::pair<int, int>& cur, const std::pair<int, int>& target) {
	return (abs(target.first - cur.first) + abs(target.second - cur.second)) * 10;
}

//judge is grid in open list
bool maze2::Astar_Manager::isGridInOpenList(Astar_Grid* target) {
	return std::find(m_openList.begin(), m_openList.end(), target) != m_openList.end();
}

//sort open list, bubble sort
void maze2::Astar_Manager::updateOpenList() {
	for (int i = 0; i < m_openList.size() - 1; i++)
	{
		for (int j = 0; j < m_openList.size() - i - 1; j++)
		{
			if (m_openList[j]->get_f_value() > m_openList[j + 1]->get_f_value())
			{
				Astar_Grid* temp{ m_openList[j] };
				m_openList[j] = m_openList[j + 1];
				m_openList[j + 1]=temp;
			}
		}
	}
}

//remove element from open list
void maze2::Astar_Manager::removeGridFromOpenList(Astar_Grid* target) {
	for (auto it = m_openList.begin(); it != m_openList.end();)
	{
		if (target == *it) {
			it = m_openList.erase(it);
		}
		else {
			++it;
		}
	}
}


//=======================================================

maze2::Astar_Manager::Astar_Manager(const std::vector<std::vector<maze2::Unit*>>& units, const std::pair<int, int>& mapScale) 
	:m_grids{ units }, m_openList{}, m_closeList{}, m_mapScale{ mapScale }, m_path{}
{
}


maze2::Astar_Manager::~Astar_Manager() {}

//core function of A star path finding
bool maze2::Astar_Manager::findPath(const std::pair<int, int>& origin, const std::pair<int, int>& target) {
	bool flag{ true };
	//polymorphism 
	Astar_Grid* start{ dynamic_cast<Astar_Grid*>(m_grids[origin.first][origin.second])};
	m_openList.push_back(start);
	Astar_Grid* curGrid{ start };

	//if open list has grids or do not find target, it will loop 
	while (m_openList.size()>0 and curGrid->getCoordinate() != target)
	{
		curGrid = m_openList[0];
		
		//if find target
		if (curGrid->getCoordinate()==target)
		{
			std::cout << "Find!\n";
			generatePath(curGrid);
			flag = true;
			break;
		}
		std::vector<Astar_Grid*> temp{selectAroundGrid(curGrid)};
		//calculate f,g,h value of grids
		for (int i = 0; i < temp.size(); i++)
		{
			int g = curGrid->get_g_value() + 10;
			if (temp[i]->get_g_value()==0 or temp[i]->get_g_value()>g)
			{
				temp[i]->set_g_value(g);
				temp[i]->setParent(curGrid);
			}
			temp[i]->set_h_value(calculManhattanDis(temp[i]->getCoordinate(), target));
			temp[i]->set_f_value(temp[i]->get_g_value() + temp[i]->get_h_value());

			if (not isGridInOpenList(temp[i]))
			{
				m_openList.push_back(temp[i]);
			}

			updateOpenList();
		}
		m_closeList.push_back(curGrid);
		removeGridFromOpenList(curGrid);
		if (m_openList.size()==0)
		{
			flag = false;
			std::cout << "Cannot Find!\n";
		}
	}

	return flag;
}

