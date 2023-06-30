//Вам необходимо реализовать сортировку пузырьком по неубыванию 
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

int bubble_sort(int* arr, int size)
{
	int i = 0;
	int count = 0;

	while (i < size - 1)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				count++;
			}
		}

		i++;
	}

	return count;
}

int main()
{
	int size;

	std::cin >> size;

	int* arr = new int[size];

	read_array(arr, size);
	int count = bubble_sort(arr, size);

	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";

	std::cout << std::endl << count;

	delete[] arr;
}