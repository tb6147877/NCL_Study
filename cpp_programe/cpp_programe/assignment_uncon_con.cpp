//#include <stdio.h>
//
//int main()
//
//{
//
//	int i, j, k;//Error1:no instantiation
//
//	for (int i = 0; i < 10; i++)//Error2, there is a variable called i
//
//	{
//   //Error3:lack of goto label:back
//		cin >> j;
//
//		if (j < 5)
//
//			goto add;
//
//		if (j > 5)
//
//			goto subtract;
//
//	}
//
//add:
//
//	k = k + i;
//
//	goto back;
//
//subtract:
//
//	k = k ¨C i;
//
//	goto back;
//
//}
//
////2.use continue to replace goto