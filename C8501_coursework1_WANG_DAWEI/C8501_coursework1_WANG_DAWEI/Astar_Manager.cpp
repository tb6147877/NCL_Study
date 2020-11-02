#include "Astar_Manager.h"

void maze1::Astar_Manager::initGrids() {
	for (int i = 0; i < m_mapScale.first; i++)
	{
		for (int j = 0; j < m_mapScale.second; j++)
		{
			m_grids[i][j] = new Astar_Grid{ m_units[i][j] };
		}
	}
}

void maze1::Astar_Manager::generatePath(Astar_Grid* grid) {
	if (grid->getParent()!=nullptr)
	{
		if (grid->getType()!= Unit::UnitType::EXIT)
		{
			grid->setType(Unit::UnitType::PATH);
		}
		generatePath(grid->getParent());
	}
}

std::vector<maze1::Astar_Grid*> maze1::Astar_Manager::selectAroundGrid(Astar_Grid* grid) {
	std::vector<maze1::Astar_Grid*> temp{};

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
		if (grids[i].first < 0 or grids[i].second < 0
			or grids[i].first >= m_mapScale.first or grids[i].second >= m_mapScale.second)
		{
			continue;
		}

		if (m_grids[grids[i].first][grids[i].second]->getType() == Unit::UnitType::WALL)
		{
			continue;
		}

		if (std::find(m_closeList.begin(), m_closeList.end(), m_grids[grids[i].first][grids[i].second]) != m_closeList.end())
		{
			continue;
		}
		temp.push_back(m_grids[grids[i].first][grids[i].second]);
	}
	return temp;
}

int maze1::Astar_Manager::calculManhattanDis(Astar_Grid* cur, Astar_Grid* target) {
	return (abs(target->getCoordinate().first - cur->getCoordinate().first) + abs(target->getCoordinate().second - cur->getCoordinate().second)) * 10;
}

int maze1::Astar_Manager::calculManhattanDis(const std::pair<int, int>& cur, const std::pair<int, int>& target) {
	return (abs(target.first - cur.first) + abs(target.second - cur.second)) * 10;
}

bool maze1::Astar_Manager::isGridInOpenList(Astar_Grid* target) {
	return std::find(m_openList.begin(), m_openList.end(), target) != m_openList.end();
}

void maze1::Astar_Manager::updateOpenList() {
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

void maze1::Astar_Manager::removeElementFromOpenList(Astar_Grid* target) {
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

maze1::Astar_Manager::Astar_Manager(const std::vector<std::vector<maze1::Unit*>>& units, const std::pair<int, int>& mapScale) 
	:m_grids{ (unsigned int)mapScale.first,std::vector<Astar_Grid*>{(unsigned int)mapScale.second} }, m_openList{}, m_closeList{}, m_mapScale{ mapScale }, m_units{units}
{
	initGrids();
}


maze1::Astar_Manager::~Astar_Manager() {
	for (int i = 0; i < m_mapScale.first; i++)
	{
		for (int j = 0; j < m_mapScale.second; j++)
		{
			delete m_grids[i][j];
		}
	}
	std::cout << "Mgr destroy\n";
}

bool maze1::Astar_Manager::findPath(const std::pair<int, int>& origin, const std::pair<int, int>& target) {
	bool flag{ true };
	Astar_Grid* start{ m_grids[origin.first][origin.second] };
	m_openList.push_back(start);
	Astar_Grid* curGrid{ start };
	while (m_openList.size()>0 and curGrid->getCoordinate() != target)
	{
		curGrid = m_openList[0];
		//curGrid->getType() == Unit::UnitType::EXIT and 
		if (curGrid->getCoordinate()==target)
		{
			std::cout << "Find!\n";
			generatePath(curGrid);
			flag = true;
			//break;
		}
		std::vector<Astar_Grid*> temp{selectAroundGrid(curGrid)};
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
		removeElementFromOpenList(curGrid);
		if (m_openList.size()==0)
		{
			flag = false;
			std::cout << "Cannot Find!\n";
		}
	}

	return flag;
}