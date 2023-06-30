//Вам необходимо реализовать сортировку простыми вставками по неубыванию
//и посчитать количество элементов, которые при добавлении к сортированной 
//части уже находились на своём месте, то есть которые не пришлось двигать.

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

int insertion_sort(int* arr, int size)
{
	int count = 1;

	for (int i = 1; i < size; i++)
	{
		int n = arr[i];
		int j = i - 1;

		while (n < arr[j] && j >= 0)
		{
			if (j == i - 1)
				count++;

			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = n;
	}

	return size - count;
}

int main()
{
	int size;

	std::cin >> size;

	int* arr = new int[size];

	read_array(arr, size);
	int count = insertion_sort(arr, size);

	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";

	std::cout << std::endl << count;

	delete[] arr;
}