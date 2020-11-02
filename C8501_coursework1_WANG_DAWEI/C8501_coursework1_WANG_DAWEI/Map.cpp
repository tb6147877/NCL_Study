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
	int temp{ Tools::getRamdom(0,m_exitNum)};
	Unit::UnitType type = temp == 0? Unit::UnitType::WALL : Unit::UnitType::SPACE;
	return type;
	
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
	//TODO IF DON'T HAVE PATH, RECREATE UNITS
	if (m_generateTimes==0)
	{
		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_column; j++)
			{
				m_units[i][j] = generateUnit(i, j);
			}
		}
		setExit();
	}
	else {
		reduceWall();
	}
	
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
				if (unit->getMapType()==Unit::MapType::EDGE and (not isBlindUnit(unit)))
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
		m_exits.push_back(edges[item]);
	}
}

void maze1::Map::reduceWall() {
	std::function<void(Unit* unit, Map* map)> func{ [&](Unit* unit, Map* map) {
				if (unit->getMapType() == Unit::MapType::NORMAL and unit->getUnitType()==Unit::UnitType::WALL)
				{
					unit->setUnitType((Unit::UnitType)Tools::getRamdom(Unit::UnitType::SPACE, Unit::UnitType::WALL));
				}
	} };
	walkMap(func);
}

bool maze1::Map::isBlindUnit(Unit* unit) {
	//These units cannot access
	//Left-Top
	if (unit->getCoordinate().first == 0 and unit->getCoordinate().second == 0)
		return true;
	//Right-Top
	if (unit->getCoordinate().first == 0 and unit->getCoordinate().second == m_column-1)
		return true;
	//Left-Bottom
	if (unit->getCoordinate().first == m_row-1 and unit->getCoordinate().second == 0)
		return true;
	//Right-Bottom
	if (unit->getCoordinate().first == m_row - 1 and unit->getCoordinate().second == m_column - 1)
		return true;
	return false;
}

//=================================================================

maze1::Map::Map(const int row, const int column, const int exitNum)
	:m_row{ row }, m_column{ column }, m_exitNum{ exitNum }, m_units{ (unsigned int)row,std::vector<Unit*>{(unsigned int)column} }
{
	m_centerX = m_row / 2;
	m_centerY = m_column / 2;
	m_generateTimes = 0;
	std::vector<Unit*> arr{};
	do
	{
		initMap();
		++m_generateTimes;
	} while (not checkHasPath(arr));
	std::cout << "The map generates " << m_generateTimes << " times.\n\n";
}


maze1::Map::~Map() {
	if (m_units.size()==0)
	{
		return;
	}
	std::function<void(Unit* unit, Map* map)> func{ [&](Unit* unit, Map* map) {
				delete unit;
	} };
	walkMap(func);
}

bool maze1::Map::checkHasPath(std::vector<Unit*>& arr) {
	bool flag{ true };
	for (int i = 0; i < getExits().size(); i++)
	{
		maze1::Astar_Manager mgr{ m_units,getMapScale() };
		maze1::Unit* target{ getExits()[i] };
		if (std::find(arr.begin(), arr.end(), target) != arr.end())
			continue;
		std::cout << "Searching:" << target->getCoordinate().first << "  " << target->getCoordinate().second << "\n";
		flag = mgr.findPath(getCenter(), target->getCoordinate());
		if (not flag)
		{
			std::cout << "Searching Failed!\n";
			break;
		}
		else {
			arr.push_back(target);
		}
	}
	std::cout << "--------------------------------------\n";

	
	return flag;
}

void maze1::Map::draw(const bool isDrawPath) {
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_units[i][j]->draw(isDrawPath);
		}
		std::cout << "\n";
	}
}

void maze1::Map::serialize(const std::string& path) {
	std::string str{""};
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			str+=m_units[i][j]->getGraphic();
		}
		if (i != m_row-1)
		{
			str += '\n';
		}
	}
	Tools::writeFile(str, path);
}


void maze1::Map::unserialize(const std::string& path) {
	int row{ 0 }, column{ 0 };
	std::vector<std::string> str = maze1::Tools::readFile(path, row, column);
	for (int i = 0; i < str.size(); i++)
	{
		std::cout << str[i] << "\n";
	}
}

