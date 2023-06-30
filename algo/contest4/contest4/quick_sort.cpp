#include <iostream>
#include "ReadWriter.h"

int count = -1;

void quickSort(int* arr, int size, int left, int right)
{
	count++;

	int i = left;
	int j = right;
	int pivot = arr[(i + j) / 2];

	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;

		while (arr[j] > pivot)
			j--;

		if (i <= j)
		{
			std::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	if (j > left)
		quickSort(arr, size, left, j);

	if (i < right)
		quickSort(arr, size, i, right);
}

int main()
{
	ReadWriter rw;

	int n = rw.readInt();

	int* arr = new int[n];

	rw.readArray(arr, n);

	quickSort(arr, n, 0, n - 1);

	rw.writeInt(count);
	rw.writeArray(arr, n);

	delete[] arr;
}
