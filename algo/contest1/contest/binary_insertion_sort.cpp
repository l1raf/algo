//Вам необходимо реализовать сортировку бинарными вставками по неубыванию 
//и посчитать количество сдвигов соседних элементов, совершённых при 
//сортировке, при этом количество сдвигов должно быть минимально.

#include <iostream>

void read_array(int* arr, int size)
{
	int num;

	for (int i = 0; i < size; i++)
	{
		std::cin >> num;
		arr[i] = num;
	}
}

int binary_search(int* arr, int num, int left, int right)
{
	int mid;

	while (left <= right)
	{
		mid = (left + right) / 2;

		if (num == arr[mid])
			return mid + 1;
		else if (num < arr[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	return left;
}

int binary_insertion_sort(int* arr, int size)
{
	int count = 0;

	for (int i = 1; i < size; i++)
	{
		int num = arr[i];
		int index = binary_search(arr, num, 0, i - 1);

		for (int j = i - 1; j >= index; j--)
		{
			arr[j + 1] = arr[j];
			count++;
		}

		arr[index] = num;
	}

	return count;
}

int main()
{
	int size;

	std::cin >> size;

	int* arr = new int[size];

	read_array(arr, size);
	int count = binary_insertion_sort(arr, size);

	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";

	std::cout << std::endl << count;

	delete[] arr;
}