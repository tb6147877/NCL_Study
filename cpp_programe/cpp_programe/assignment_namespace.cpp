//#include <iostream> 
//
//using namespace std;
//
//namespace luke { int dark = 0; int light = 10; }
//
//namespace anakin { int dark = 10; int light = 0; }
//
//int main() {
//
//	using luke::dark;
//
//	using anakin::light;
//
//	cout << dark + light << endl; // (1) "0", because above using::
//
//	{
//
//		int dark = 5;
//
//		cout << light + dark << endl; // (2)"5", dark is the local variable
//
//		for (int dark = 0; dark < luke::light; dark++) {
//
//			anakin::dark = anakin::dark + dark;
//
//			cout << dark << endl; //(3) "0-9", this dark instantiates in the for()
//
//		}
//
//	}
//
//	cout << anakin::dark + anakin::light; //(4)"55" 10+0+1+2+...+9
//
//	{
//
//		cout << dark << endl; //(5)"0"
//
//	}
//
//};
//
////Namespces are used to avoid name collision.