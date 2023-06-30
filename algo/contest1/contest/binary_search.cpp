//Даны два целочисленных массива A[N] и B[K].
//Массив A упорядочен по убыванию.Массив B никак не упорядочен.
//Необходимо определить, встречаются ли элементы массива B в массиве A.
//При решении используйте двоичный поиск.

#include <iostream>
#include <vector>

void fill_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		int num;
		std::cin >> num;
		arr[i] = num;
	}
}

int binary_search(int* a, int num, int size)
{
	int left = 0;
	int right = size - 1;
	int mid;

	while (left <= right)
	{
		mid = left + (right - left) / 2;

		if (a[mid] == num)
			return mid;
		else if (a[mid] > num)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return -1;
}

int main()
{
	int n, k;

	std::cin >> n >> k;

	int* a = new int[n];
	int* b = new int[k];

	fill_array(a, n);
	fill_array(b, k);

	for (int i = 0; i < k; i++)
	{
		if (binary_search(a, b[i], n) == -1)
			std::cout << "NO" << std::endl;
		else
			std::cout << "YES" << std::endl;
	}

	delete[] a;
	delete[] b;
}