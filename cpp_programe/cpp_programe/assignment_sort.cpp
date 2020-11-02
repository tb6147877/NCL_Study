#include <iostream>
#include <vector>

//1.easiest sort function-bubble sort
void bubble_sort(std::vector<int>& arr) {
	for (int i = 0; i < arr.size()-1; i++)
	{
		for (int j = 0; j < arr.size() -i-1; j++)
		{
			if (arr[j]>arr[j+1])
			{
				arr[j] = arr[j] ^ arr[j + 1];
				arr[j + 1]= arr[j] ^ arr[j + 1];
				arr[j] = arr[j] ^ arr[j + 1];
			}
		}
	}
}

//2.fastest sort function-quick sort
void quick_sort(std::vector<int>& arr, const int left, const int right) {
	if (left<right)
	{
		//x is the flag number of the array
		int x = arr[left], i = left, j = right;
		while (i < j)//if i=j, the whole array complete a search
		{
			//search from right to left, if find a number less than the flag number, put the number into left of the middle
			while (i < j)
			{
				if (arr[j]<=x)
				{
					arr[i] = arr[j];
					break;
				}
				else {
					j--;
				}
			}

			//search from left to right, if find a number greater than the flag number, put the number into right of the middle
			while (i < j)
			{
				if (arr[i] > x)
				{
					arr[j] = arr[i];
					break;
				}
				else {
					i++;
				}
			}
		}
		//out of loop, now the flag number is at the middle of the array
		arr[i] = x;
		//recursion
		quick_sort(arr, left, i - 1);
		quick_sort(arr, i + 1, right);
	}
}


int main() {
	std::vector<int> arr{ -1,99,8,0,5,10,100,-90 };
	bubble_sort(arr);

	//left is the index of the first element of the array, and the right is the last. 
	//quick_sort(arr, 0, arr.size() - 1);

	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << "\n";
	}

	return 0;
}