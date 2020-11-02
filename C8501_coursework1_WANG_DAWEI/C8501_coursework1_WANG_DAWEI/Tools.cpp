#include "Tools.h"

int maze1::Tools::getRamdom(int min, int max) {
	std::uniform_int_distribution<> die{ min, max };
	return die(mersenne);
}

std::vector<std::string> maze1::Tools::readFile(const std::string& path, int& row, int& column) {
	char buf[1024];
	row = 0;
	column = 0;
	std::string str{ "" };
	std::vector<std::string> temp{};

	std::ifstream file;
	file.open(path, std::ios::in);
	for (; !file.eof();)
	{
		file.getline(buf, 1024);
		str = "";
		column = 0;
		for (int i = 0; i < sizeof(buf)/ sizeof(char); i++)
		{
			if (buf[i]>0)
			{
				str += buf[i];
				++column;
			}
			else
			{
				continue;
			} 
		}
		++row;
		//std::cout << buf << std::endl;
		temp.push_back(str);
	}

	file.close();
	return temp;
}

void maze1::Tools::writeFile(const std::string& content, const std::string& path) {
	std::fstream file;
	file.open(path, std::ios::out);
	file << content;
	file.close();
}

bool maze1::Tools::hasFile(const std::string& path) {
	std::fstream _file;
	_file.open(path, std::ios::in);
	_file.close();
	return (!_file)?false:true;
	/*if (!_file)
	{
		std::cout << 111;
		return false;
	}
	else {
		std::cout << 222;
		return true;
	}*/
}

int maze1::Tools::getNumber(const std::string& discribe) {
	std::cout <<discribe<<"\n";
	int temp{};
	std::cin >> temp;
	std::cin.ignore(32767, '\n');
	return temp;
}