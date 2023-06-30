#include <iostream>

void readIntervals(int* left, int* right, int size)
{
	int lNum;
	int rNum;

	for (int i = 0; i < size; i++)
	{
		std::cin >> lNum >> rNum;
		left[i] = lNum;
		right[i] = rNum;
	}
}

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

		if (largest <= heapSize / 2 - 1)
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

//Находит индекс числа, которое больше х
int getIndexOfGreaterNumber(int* arr, int size, int x)
{
	int left = 0;
	int right = size - 1;
	int index = -1;

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (arr[mid] <= x)
		{
			left = mid + 1;
		}
		else
		{
			index = mid;
			right = mid - 1;
		}
	}

	return index;
}

int getNumberOfIntervals(int* left, int* right, int size, int x)
{
	//Берем интервалы, которые подходят по левой границе,
	//и выбрасываем те, которые не подходят по правой границе

	//Количество интервалов, левая граница которых меньше или равна х
	int leftCount = getIndexOfGreaterNumber(left, size, x);

	if (leftCount == -1)
		leftCount = size;

	//Количество интервалов, правая граница которых меньше или равна х
	int rightCount = getIndexOfGreaterNumber(right, size, x);

	if (rightCount == -1)
		rightCount = size;

	return leftCount - rightCount > 0 ? leftCount - rightCount : 0;
}

void answer(int* left, int* right, int size)
{
	int numberOfQuestions;
	std::cin >> numberOfQuestions;

	for (int i = 0; i < numberOfQuestions; i++)
	{
		int question;
		std::cin >> question;
		std::cout << getNumberOfIntervals(left, right, size, question) << "\n";
	}
}

int main()
{
	int n;

	std::cin >> n;

	int* left = new int[n];
	int* right = new int[n];

	readIntervals(left, right, n);

	heapSort(left, n);
	heapSort(right, n);

	answer(left, right, n);

	delete[] left;
	delete[] right;
}