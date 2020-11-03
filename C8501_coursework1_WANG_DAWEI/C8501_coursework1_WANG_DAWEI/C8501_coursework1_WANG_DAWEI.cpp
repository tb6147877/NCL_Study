#include <iostream>
#include <map>
#include <utility>
#include <fstream>


#include "Map.h"
#include "Tools.h"
#include "Astar_Manager.h"

#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define CYAN "\033[36m" /* Cyan */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */

//keep asking an option from user, and do the validity check
//return: 1 or 2
int askOption() {
	while (true)
	{
		char a{};
		std::cin >> a;
		std::cin.ignore(32767, '\n');

		if (a == '1')
		{
			return 1;
		}
		else if (a == '2')
		{
			return 0;
		}
		else {
			std::cout << "#############################################################################" << "\n";
			std::cout << "Sorry, please enter a valid option" << "\n";
			continue;
		}
	}
}

//keep asking a number from user, and do the validity check
//para: the number must greater than max
//return: the number 
int askRowAndCol(const int max) {
	while (true)
	{
		int a{};
		std::cin >> a;
		std::cin.ignore(32767, '\n');

		if (!std::cin.fail() and a>=max)
		{
			return a;
		}
		else 
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "#############################################################################" << "\n";
			std::cout << "Sorry, please enter a valid number" << "\n";
			continue;
		}
	}
}

//keep asking a number from user, and do the validity check
//para: the number must equal or less than max
//return: the number 
int askExitNum(const int max) {
	while (true)
	{
		int a{};
		std::cin >> a;
		std::cin.ignore(32767, '\n');

		if (!std::cin.fail() and a > 0 and a<=max)
		{
			return a;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "#############################################################################" << "\n";
			std::cout << "Sorry, please enter a valid number" << "\n";
			continue;
		}
	}
}

//keep asking a file path from user, and check if there is a file in the path 
//return: the path 
std::string askPath() {
	std::string str{ "" };
	while (true)
	{
		std::cin >> str;
		std::cin.ignore(32767, '\n');

		if (maze1::Tools::hasFile(str))
		{
			return str;
		}
		else {
			std::cout << "#############################################################################" << "\n";
			std::cout << "Sorry, please enter a valid file path" << "\n";
			continue;
		}
	}
}

//ask a string from user
//return: the string
std::string askString() {
	std::string str{ "" };
	std::cin >> str;
	std::cin.ignore(32767, '\n');
	return str;
}


//Save the map
//para:a reference of map class
void doMapSave(maze1::Map& map) {
	std::cout << "#############################################################################" << "\n";
	std::cout << "Do you want to save your map? (1-yes/2-no)" << "\n";
	int opt{ -1 };
	opt = askOption();

	if (opt==1)
	{
		std::cout << "Please enter a file name to save your map" << "\n";
		std::string name{ askString() };
		std::string path{ maze1::Tools::getDesktopPath() + '/' + name };
		map.serialize(path);
		std::cout << "Your map file has been saved in "<<path << "\n";
		std::cout << "Program End! Thank you!" << "\n";
	}
	else {
		std::cout << "Program End! Thank you!" << "\n";
	}
}

//generate an object of map class to do generating map and finding path
void doMapGenerate() {
	std::cout << "#############################################################################" << "\n";
	std::cout << "Welcome to Map Generating&Path Finding, please enter the ROW number of your map" << "\n";
	std::cout << "Note: According to rules, the ROW number MUST Equal or Greater than 5" << "\n";
	int row{ askRowAndCol(5) };
	std::cout << "Please enter the COLUMN number of your map" << "\n";
	std::cout << "Note: According to rules, the COLUMN number MUST Equal or Greater than 5" << "\n";
	int column{ askRowAndCol(5) };
	int limit{ row * 2 + column * 2 - 4 };
	std::cout << "Please enter the EXIT number of your map" << "\n";
	std::cout << "Note: According to your ROW&COLUMN, the EXIT number MUST Greater than 0 and Equal or LESS than :" << limit<<"\n";
	int exitNum{ askExitNum(limit) };

	maze1::Map map{ row,column,exitNum };
	map.draw();

	doMapSave(map);
}

//load map and show map with a map object
void doMapLoad() {
	std::cout << "#############################################################################" << "\n";
	std::cout << "Welcome to Map Loading, please enter the absolute path of your map" << "\n";
	std::string path{ askPath() };
	maze1::Map map{};
	map.unserialize(path);
	std::cout << "Program End! Thank you!" << "\n";
}



int main()
{
	std::cout<< "Welcome to Maze1, C8501 courework, I am Wang Dawei " << "\n";
	std::cout << "#############################################################################" << "\n";
	std::cout << "If you want to generate map and find path, please type 1 and press Enter " << "\n";
	std::cout << "If you want to load map in the file and show it, please type 2 and press Enter " << "\n";

	int opt{ -1 };
	opt=askOption();
	opt == 1 ? doMapGenerate() : doMapLoad();















	/*bool flag=maze1::Tools::hasFile("C:/Users/10626/Desktop/cpp_test1");

	if (flag)
	{
		std::cout << 111;
	}
	else {
		std::cout << 222;
	}*/

	/*maze1::Map map{ 5,5,1 };
	map.draw();*/
	/*map.serialize("C:/Users/10626/Desktop/cpp_test1");
	std::cout << "\n=================================\n";
	map.unserialize("C:/Users/10626/Desktop/cpp_test1");*/
	//maze1::Tools::writeFile("111\n333\n666","C:/Users/10626/Desktop/cpp_test1");
}

