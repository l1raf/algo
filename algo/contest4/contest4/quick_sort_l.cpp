#include <iostream>
#include "ReadWriter.h"

int count = -1;

int lomutoPartition(int* arr, int left, int right)
{
	int pivot = arr[right];
	int i = left;

	for (int j = left; j <= right - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			std::swap(arr[i], arr[j]);
			i++;
		}
	}

	std::swap(arr[i], arr[right]);

	return i;
}

void quickSort(int* arr, int left, int right)
{
	if (left < right)
	{
		count++;
		int p = lomutoPartition(arr, left, right);

		if (p > 0)
			quickSort(arr, left, p - 1);
		quickSort(arr, p + 1, right);
	}
}

int main()
{
	ReadWriter rw;

	int n = rw.readInt();

	int* arr = new int[n];

	rw.readArray(arr, n);

	quickSort(arr, 0, n - 1);

	rw.writeInt(count);
	rw.writeArray(arr, n);

	delete[] arr;
}
