#include "Map.h"

maze1::Unit::MapType maze1::Map::judgeMapType(const int x, const int y) {
	Unit::MapType temp{ Unit::MapType::NORMAL };
	if (x==m_centerX and y==m_centerY)
	{
		temp = Unit::MapType::CENTER;
	}
	else if (x<=m_centerX+1 and x>=m_centerX-1 and y<=m_centerY+1 and y>=m_centerY-1)
	{
		temp = Unit::MapType::CENTER_REGION;
	}
	else if (x==0 or x==m_row-1 or y==0 or y==m_column-1)
	{
		temp = Unit::MapType::EDGE;
	}
	return temp;
}

maze1::Unit::UnitType maze1::Map::randomUnitType() {
	return (Unit::UnitType)Tools::getRamdom(Unit::UnitType::SPACE, Unit::UnitType::WALL);
}

maze1::Unit* maze1::Map::generateUnit(const int x, const int y) {
	Unit::MapType mapType = judgeMapType(x, y);
	Unit::UnitType unitType{};
	switch (mapType)
	{	
	case Unit::MapType::CENTER :
		unitType = Unit::UnitType::ORIGIN;
		break;
	case Unit::MapType::CENTER_REGION:
		unitType = Unit::UnitType::SPACE;
		break;
	case Unit::MapType::EDGE:
		unitType = Unit::UnitType::WALL;
		break;
	case Unit::MapType::NORMAL:
		unitType = randomUnitType();
		break;

	}
	return generateUnit(x,y,unitType,mapType);
}

maze1::Unit* maze1::Map::generateUnit(const int x, const int y, const Unit::UnitType type, const Unit::MapType mapType) {
	return new Unit{ x,y ,type,mapType };
}

void maze1::Map::initMap() {
	m_centerX = m_row / 2;
	m_centerY = m_column / 2;

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_units[i][j] = generateUnit(i,j);
		}
	}
	setExit();
}

void maze1::Map::walkMap(const std::function<void(Unit* unit, Map* map)>& func) {
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			func(m_units[i][j], this);
		}
	}
}

void maze1::Map::setExit() {
	int curNum{ 0 };
	std::vector<Unit*> edges{};
	std::function<void(Unit* unit, Map* map)> func{ [&](Unit* unit, Map* map) {
				if (unit->getMapType()==Unit::MapType::EDGE)
				{
					edges.push_back(unit);
				}
	} };
	walkMap(func);
	if (m_exitNum>edges.size())
	{
		std::cout << "Error: Exit number:" << m_exitNum << " is greater than edges:" << edges.size() << '\n';
		return;
	}
	std::vector<int> exits{};
	do
	{
		if (exits.size()==0)
		{
			exits.push_back(Tools::getRamdom(0, edges.size() - 1));
		}
		else {
			int temp{ Tools::getRamdom(0, edges.size() - 1) };
			while (temp==exits[exits.size()-1])
			{
				temp=Tools::getRamdom(0, edges.size() - 1);
			}
			exits.push_back(temp);
		}
	} while (exits.size()<m_exitNum);
	for (auto  item: exits)
	{
		edges[item]->setUnitType(Unit::UnitType::EXIT);
	}
}

//=================================================================

maze1::Map::Map(const int row, const int column, const int exitNum)
	:m_row{ row }, m_column{ column }, m_exitNum{ exitNum }, m_units{ (unsigned int)row,std::vector<Unit*>{(unsigned int)column} }
{
	do
	{
		initMap();
	} while (not checkHasPath());
}
maze1::Map::~Map() {}

bool maze1::Map::checkHasPath() { return true; }

void maze1::Map::draw() {
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_units[i][j]->draw();
		}
		std::cout << "\n";
	}
}

