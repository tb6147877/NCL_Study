#include <iostream>

//1.
void func1() {
	char name[]{ "Wang Dawei" };
	int counter{ 0 };
	while (name[counter]!='\0')
	{
		std::cout << name[counter++];
	}
}

//2.
void func2() {
	char name[]{ "Wang Dawei" };
	int counter{ 0 };
	bool flag{ false };

	char* first{ new char[5] };
	int len_f{ 0 };
	char* last{ new char[6] };
	int len_l{ 0 };

	while (name[counter] != '\0')
	{
		if (not flag)
		{
			flag = name[counter] == ' ';
		}
		
		if (flag)
		{
			if (name[counter] != ' ')
			{
				last[len_l++] = name[counter];
			}
		}
		else {
			if (name[counter] != ' ')
			{
				first[len_f++] = name[counter];
			}
		}
		counter++;
	}

	first[len_f] = '\0';
	last[len_l] = '\0';
	counter = 0;
	while (first[counter]!='\0')
	{
		std::cout << first[counter++];
	}
	std::cout << '\n';
	counter = 0;
	while (last[counter] != '\0')
	{
		std::cout << last[counter++];
	}

	delete[] first;
	delete[] last;
}

//3.



int main() {
	//func1();
	//func2();
}