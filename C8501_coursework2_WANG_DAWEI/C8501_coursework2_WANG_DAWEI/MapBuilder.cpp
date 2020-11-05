#include "MapBuilder.h"


std::vector<maze2::Unit*> maze2::MapBuilder::analysisOneLine(const std::string& str, const int row) {
	std::vector<maze2::Unit*> temp{};
	for (int i = 0; i < str.size(); i++)
	{
		Unit::UnitType type{ Unit::UnitType::SPACE };
		switch (str[i])
		{
		case ' ':
		case 'o':
			type = Unit::UnitType::SPACE;
			break;
		case 'F':
			type = Unit::UnitType::ORIGIN;
			break;
		case 'X':
			type = Unit::UnitType::WALL;
			break;
		case 'E':
			type = Unit::UnitType::EXIT;
			break;
		/*case 'o':
			type = Unit::UnitType::PATH;
			break;*/
		}
		temp.push_back(new Astar_Grid{ row,i,type,Unit::MapType::NORMAL });
	}

	return temp;
}

//=========================================================

maze2::Map maze2::MapBuilder::buildMap(const std::string& path) {
	int row{ 0 }, column{ 0 };
	std::vector<std::string> str = maze2::Tools::readFile(path, row, column);

	std::vector<std::vector<maze2::Unit*>> units{};
	for (int i = 0; i < str.size(); i++)
	{
		units.push_back(analysisOneLine(str[i], i));
	}

	int centerX{ row / 2 }, centerY{ column / 2 };

	std::vector<maze2::Unit*> exits{};
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (units[i][j]->getUnitType()==Unit::UnitType::EXIT)
			{
				exits.push_back(units[i][j]);
			}
		}
	}

	return Map{units,row,column,(int)exits.size(),centerX,centerY,exits};
}
