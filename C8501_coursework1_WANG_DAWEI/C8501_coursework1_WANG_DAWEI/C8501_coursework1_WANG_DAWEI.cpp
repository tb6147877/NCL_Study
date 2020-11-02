// C8501_coursework1_WANG_DAWEI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <utility>

#include "Map.h"
#include "Tools.h"
#include "Astar_Manager.h"

int main()
{
	//std::cout<<maze1::Tools::getRamdom(0, 2)<<"\n";
	/*maze1::Unit unit{ 4,5,maze1::Unit::UnitType::CENTER };
    std::cout << "Hello World!\n";*/

	/*std::map<int, char> map{};
	map.insert(std::pair<int, char>{6, 'a'});
	map.insert(std::pair<int, char>{4, 'b'});
	map.insert(std::pair<int, char>{0, 'c'});
	map.insert(std::pair<int, char>{-1, 'z'});
	std::map<int, char>::iterator it = map.begin();
	for (it = map.begin(); it != map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << (map.begin())->second;*/

	maze1::Map map{ 20,80,6 };
	/*maze1::Astar_Manager mgr{ &map };
	maze1::Unit* target{ map.getEdges()[0] };
	mgr.findPath(map.getCenter(), target->getCoordinate());*/
	map.draw();
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
