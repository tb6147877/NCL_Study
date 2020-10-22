//#include <iostream>
//#include <functional>
//
////1.
//void product(const int a, const int b) {
//	std::cout << a * b<<'\n';
//}
//
////2.
//double quotient(const double a,const int b) {
//	return a / b;
//}
//
////3.
//int getNumber() {
//	std::cout << "please enter a number\n";
//	int length{};
//	std::cin >> length;
//	std::cin.ignore(32767, '\n');
//	return length;
//}
//
//char getOperator() {
//	std::cout << "please enter an operator\n";
//	char length{};
//	std::cin >> length;
//	std::cin.ignore(32767, '\n');
//	return length;
//}
//
//int add(int i, int j) {
//	return j + i;
//}
//
//int min(int i, int j) {
//	return i - j;
//}
//
//int pro(int i, int j) {
//	return j * i;
//}
//
//int quo(int i, int j) {
//	return i / j;
//}
//
//typedef std::function<int(int, int)> calFunc;
//
//int main()
//{
//	int num1{ getNumber() };
//	int num2{ getNumber() };
//	char op{ getOperator() };
//	calFunc func;
//	switch (op)
//	{
//	case '+':
//		func = add;
//		break;
//	case '-':
//		func = min;
//		break;
//	case '*':
//		func = pro;
//		break;
//	case '/':
//		func = quo;
//		break;
//	default:
//		break;
//	}
//	
//	std::cout << func(num1, num2);
//}
