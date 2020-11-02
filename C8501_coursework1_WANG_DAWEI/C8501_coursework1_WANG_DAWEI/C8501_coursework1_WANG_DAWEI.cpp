#include <iostream>
#include <map>
#include <utility>
#include <fstream>

#include "Map.h"
#include "Tools.h"
#include "Astar_Manager.h"

int main()
{


	maze1::Map map{ 20,80,1 };
	map.draw();
	map.serialize("C:/Users/10626/Desktop/cpp_test1");
	std::cout << "\n=================================\n";
	map.unserialize("C:/Users/10626/Desktop/cpp_test1");
	//maze1::Tools::writeFile("111\n333\n666","C:/Users/10626/Desktop/cpp_test1");
}

