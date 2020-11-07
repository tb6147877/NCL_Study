#include "Map.h"

//decide what a MapType it is of a position on the map
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

//random a UnitType
maze1::Unit::UnitType maze1::Map::randomUnitType() {
	//random wall independent on exit number, more exits less walls
	int temp{ Tools::getRamdom(0,m_exitNum)};
	Unit::UnitType type = temp == 0? Unit::UnitType::WALL : Unit::UnitType::SPACE;
	return type;
	
}

//generate a unit 
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

//actually generate a unit 
maze1::Unit* maze1::Map::generateUnit(const int x, const int y, const Unit::UnitType type, const Unit::MapType mapType) {
	return new Unit{ x,y ,type,mapType };
}

//generate the whole map
void maze1::Map::initMap() {
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

//go through every unit on the map and excute the function
//para:a function pointer
void maze1::Map::walkMap(const std::function<void(Unit* unit, Map* map)>& func) {
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			func(m_units[i][j], this);
		}
	}
}

//set exits on the map
void maze1::Map::setExit() {
	int curNum{ 0 };
	std::vector<Unit*> edges{};
	//1.get all the unit which can be a exit
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

	//2.produce exits
	std::vector<int> exits{};
	do
	{
		//random a index of edges
		if (exits.size()==0)
		{
			exits.push_back(Tools::getRamdom(0, edges.size() - 1));
		}
		else {
			//if index is duplicate, random again in loopdui
			int temp{ Tools::getRamdom(0, edges.size() - 1) };
			while (temp==exits[exits.size()-1])
			{
				temp=Tools::getRamdom(0, edges.size() - 1);
			}
			exits.push_back(temp);
		}
	} while (exits.size()<m_exitNum);

	//3.store exits
	for (auto  item: exits)
	{
		//set unit type
		edges[item]->setUnitType(Unit::UnitType::EXIT);
		//store exits
		m_exits.push_back(edges[item]);
	}
}

//if the map don't have a path, this function is needed
void maze1::Map::reduceWall() {
	std::function<void(Unit* unit, Map* map)> func{ [&](Unit* unit, Map* map) {
				if (unit->getMapType() == Unit::MapType::NORMAL and unit->getUnitType()==Unit::UnitType::WALL)
				{
					unit->setUnitType((Unit::UnitType)Tools::getRamdom(Unit::UnitType::SPACE, Unit::UnitType::WALL));
				}
	} };
	walkMap(func);
}



void maze1::Map::increaseWall() {
	std::function<void(Unit* unit, Map* map)> func{ [&](Unit* unit, Map* map) {
				if (unit->getUnitType() == Unit::UnitType::SPACE)
				{
					unit->setUnitType((Unit::UnitType)Tools::getRamdom(Unit::UnitType::SPACE, Unit::UnitType::WALL));
				}
	} };
	walkMap(func);
}

//in the map, there is 4 points cannot be an exit because they can lead to no path, there are 4 corners
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
	} while (not checkHasPath(arr));//check wether there is a path
	std::cout << "The map generates " << m_generateTimes << " times.\n\n";
	increaseWall();
}


maze1::Map::~Map() {
	//free memory
	if (m_units.size()==0)
	{
		return;
	}
	std::function<void(Unit* unit, Map* map)> func{ [&](Unit* unit, Map* map) {
				delete unit;
	} };
	walkMap(func);
}

//check wether this map has a path
//arr strore all targets which have find path
bool maze1::Map::checkHasPath(std::vector<Unit*>& arr) {
	bool flag{ true };
	for (int i = 0; i < getExits().size(); i++)
	{
		//call Astar path finding
		maze1::Astar_Manager mgr{ m_units, getMapScale() };
		maze1::Unit* target{ getExits()[i] };

		//if this exit has a path,skip
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

//draw the whole map
//para:if isDrawPath equals true, path symbol 'o' will be draw; otherwise draw space symbol ' '
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

//save map to disk
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

//read file from disk
void maze1::Map::unserialize(const std::string& path) {
	int row{ 0 }, column{ 0 };
	std::vector<std::string> str = maze1::Tools::readFile(path, row, column);
	for (int i = 0; i < str.size(); i++)
	{
		std::cout << str[i] << "\n";
	}
}

