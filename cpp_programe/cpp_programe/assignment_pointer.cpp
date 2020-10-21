//1.
//&a=28c
//p1=ec0
//&p1=290
//*p1=2
//p2=290
//&p2=298
//**p2=Error, p2 has been deleted
//p3=ee0
//&p3=2a0
//&**p3=Error, p3 has been deleted

//2.
//&a=28c
//p1=28c
//&p1=290
//*p1=1
//p2=290
//&p2=298
//**p2=Error, p2 has been deleted
//p3=ee0
//&p3=298
//&**p3=Error, p3 has been deleted
#include <iostream>
int main() {
	int a = 1;
	std::cout << &a << '\n';

	/*int *p1 = new int(2);
	std::cout<<*/


	int** p3 = new int*;
	*p3 = &a;

	delete p3;

	std::cout << &p3;
}