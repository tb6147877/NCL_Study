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


int main() {
	func1();
}