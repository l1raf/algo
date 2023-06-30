//Вам необходимо реализовать сортировку выбором минимума по неубыванию 
//и посчитать количество обменов совершённых при сортировке.

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

int selection_sort(int* arr, int size)
{
	int count = 0;

	for (int i = 0; i < size - 1; i++)
	{
		int min_index = i;

		for (int j = i + 1; j < size; j++)
			if (arr[j] < arr[min_index])
				min_index = j;

		if (min_index != i)
		{
			std::swap(arr[i], arr[min_index]);
			count++;
		}
	}

	return count;
}

int main()
{
	int size;

	std::cin >> size;

	int* arr = new int[size];

	read_array(arr, size);
	int count = selection_sort(arr, size);

	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";

	std::cout << std::endl << count;

	delete[] arr;
}