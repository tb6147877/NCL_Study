#include <iostream>

//1.
//(1)stack overflow is an error happened when we allocate too  many memory on stack or do too many nest function call.
//(2)because recursion do some nest function call.
//(3)we create a very big static array in main() can also create a stack overflow.
//void func1() {
//	int arr[100000];
//}

//2.
//(1)mainly heap, but it is also happened in stack.
//(2)using pointer carefully or maybe sometimes use smart pointer is better.
//(3)
void func2() {
	int* ptr1;
	{
		int a = 5;
		ptr1 = &a;
	}
	std::cout << *ptr1;
	int b = 6;
	ptr1 = &b;
	//I am not very sure.
}


int main() {
	func2();

}
