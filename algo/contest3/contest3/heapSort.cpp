#include "ReadWriter.h";

void heapify(int* arr, int heapSize, int i)
{
	int largest = i;

	if (2 * i + 1 < heapSize && arr[2 * i + 1] > arr[i])
		largest = 2 * i + 1;

	if (2 * i + 2 < heapSize && arr[2 * i + 2] > arr[largest])
		largest = 2 * i + 2;

	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		heapify(arr, heapSize, largest);
	}
}

void buildHeap(int* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i);
}

void heapSort(int* arr, int size)
{
	buildHeap(arr, size);

	for (int i = size - 1; i >= 1; i--)
	{
		std::swap(arr[0], arr[i]);
		size--;
		heapify(arr, size, 0);
	}
}

int main()
{
	ReadWriter rw;

	int n = rw.readInt();

	int* arr = new int[n];

	rw.readArray(arr, n);

	heapSort(arr, n);

	rw.writeArray(arr, n);

	delete[] arr;
}