#include "ReadWriter.h"

int depth;

void heapify(int* arr, int heapSize, int i, int h = 0)
{
	if (h > depth)
		depth = h;

	int largest = i;

	if (2 * i + 1 < heapSize && arr[2 * i + 1] > arr[i])
		largest = 2 * i + 1;

	if (2 * i + 2 < heapSize && arr[2 * i + 2] > arr[largest])
		largest = 2 * i + 2;

	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);

		if (largest <= heapSize / 2 - 1)
			heapify(arr, heapSize, largest, ++h);
	}
}

void buildHeap(int* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i);
}

int main()
{
	ReadWriter rw;

	int n = rw.readInt();

	int* arr = new int[n];

	rw.readArray(arr, n);

	buildHeap(arr, n);

	rw.writeInt(depth);
	rw.writeArray(arr, n);

	delete[] arr;
}