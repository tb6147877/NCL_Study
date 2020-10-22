//#include <iostream>
//
////1.
//bool f1(const int n) {
//	return n >= 0;
//}
//
////2.
//void ask4Num() {
//	int n{};
//	do
//	{
//		std::cout << "please enter a number";
//		std::cin >> n;
//	} while (not f1(n));
//}
//
////3.
////Advantage: ?
////Disadvantage: ?
//void ask4Num_recursion() {
//	int n{};
//	std::cout << "please enter a number";
//	std::cin >> n;
//	if (not f1(n))
//	{
//		ask4Num_recursion();
//	}
//}
//
//int main() {
//	ask4Num_recursion();
//}