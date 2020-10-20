#include <iostream>

//This function can copy elements in the b to a.  a and b are dynamic char arraies. It is a deep copy.
//Actually the size of a must equal or greater than b.
void v1(char* a, const char* b) {

	while (*b != '\0') {

		*a = *b;

		a++;

		b++;

	}

	*a = '\0';

}

//In this new function, I use comma operator and postfix increment operator.
void new_v1(char* a, const char* b) {

	while (*a = '\0',*b != '\0')
		*(a++) = *(b++);

}

int main()
{
	char* x = new char[11];
	char* y = new char[11]{ "helloworld" };
	new_v1(x, y);
	std::cout <<x;

	//Question, why this can work?
	/*y[12] = 'a';
	std::cout << y[12];*/
}


/*
char x = new char[5];//Error1, this should be "char* x", it must be a pointer

char y = new char[10];//same as above

char *a = x[0];//Error2, this should be "&x[0]", it must be an address

char *b = y[4];//same as above

//Error3, x and y haven't been instantiated, they have undefined value.

v1(a, b);//Error4, b has 6 chars, but a can only store 5 chars, this will produce error within v1.
*/


