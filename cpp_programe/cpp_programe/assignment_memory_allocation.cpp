//#include <iostream>
//
////1.
////(1)stack overflow is an error happened when we allocate too  many memory on stack or do too many nest function call.
////(2)because recursion do some nest function call.
////(3)we create a very big static array in main() can also create a stack overflow.
////void func1() {
////	int arr[100000];
////}
//
////2.
////(1)I think it cannot happened in stack.
////(2)using pointer carefully or maybe sometimes use smart pointer is better.
////(3)I cannot.
//
////3.
////(1)use delete[] to reclaim an array on the heap in one go.
////(2)all the integer values are stored on the stack while their references (poitners pointing to them) are on the heap
//void func3() {
//	int arr[5]{ 0,1,2,3,4 };
//	int **ptr{ new int*{&arr[0]} };
//	for (int i = 0; i < 5; i++)
//	{
//		std::cout << *(*ptr + i)<<"\n";
//	}
//	delete ptr;
//	ptr = nullptr;
//	std::cout << "===========================\n";
//	for (int i = 0; i < 5; i++)
//	{
//		std::cout << arr[i] << "\n";
//	}
//}
//
//
//int main() {
//	//func2();
//	func3();
//}
