#include "ReadWriter.h"

//Сортировка подсчетом в порядке невозрастания
void countingSort(int* ids, int* power, int size)
{
	int* sortedIds = new int[size];
	int max = power[0];
	int* A = new int[size];

	for (int i = 0; i < size; i++)
	{
		A[i] = power[i];

		if (power[i] > max)
			max = power[i];
	}

	int k = max + 1;

	//Вспомогательный массив
	int* C = new int[k];

	for (int i = 0; i < k; i++)
		C[i] = 0;

	for (int i = 0; i < size; i++)
		C[A[i]]++;

	for (int i = 1; i < k; i++)
		C[i] += C[i - 1];

	for (int i = 0; i < size; i++)
	{
		sortedIds[std::abs(C[A[i]] - size)] = ids[i];
		power[std::abs(C[A[i]] - size)] = A[i];
		C[A[i]]--;
	}

	for (int i = 0; i < size; i++)
		ids[i] = sortedIds[i];

	delete[] A;
	delete[] C;
	delete[] sortedIds;
}

int main()
{
	ReadWriter rw;

	int n = rw.readInt();

	int* ids = new int[n];
	int* power = new int[n];

	rw.readArrays(ids, power, n);
	countingSort(ids, power, n);
	rw.writeArrays(ids, power, n);

	delete[] ids;
	delete[] power;
}