#include "ReadWriter.h"

int findLastIndexOfHeapElement(int* arr, int size)
{
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		if (2 * i + 1 < size && arr[i] >= arr[2 * i + 1])
		{
			index++;

			if (2 * i + 2 < size && arr[i] >= arr[2 * i + 2])
				index++;
			else
				return index;
		}
		else
		{
			return index;
		}
	}

	return index;
}

int main()
{
	ReadWriter rw;

	int n = rw.readInt();

	int* arr = new int[n];

	rw.readArray(arr, n);

	int ans = findLastIndexOfHeapElement(arr, n);

	rw.writeInt(ans);

	delete[] arr;
}