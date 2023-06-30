#include <iostream>
#include <fstream>

union U
{
	unsigned int a; // occupies 4 bytes
	unsigned char b[4]; // occupies 4 bytes
};

void readArray(U* u, int length, std::fstream& fin)
{
	if (fin.is_open())
	{
		for (int i = 0; i < length; i++)
			fin >> u[i].a;

		fin.close();
	}
}

void writeArray(U* u, int n)
{
	std::fstream fout;
	fout.open("output.txt", std::ios::out);

	if (fout.is_open())
	{
		for (int i = 0; i < n; i++)
			fout << u[i].a << " ";

		fout.close();
	}
}

//Сортировка подсчётом, переделанная под union
void countingSort(U* B, int size, int i)
{
	int max = B[0].b[i];
	U* A = new U[size];

	for (int j = 0; j < size; j++)
	{
		A[j] = B[j];

		if (B[j].b[i] > max)
			max = B[j].b[i];
	}

	int k = max + 1;

	//Вспомогательный массив
	int* C = new int[k];

	for (int j = 0; j < k; j++)
		C[j] = 0;

	for (int j = 0; j < size; j++)
		C[A[j].b[i]]++;

	for (int j = 1; j < k; j++)
		C[j] += C[j - 1];

	for (int j = size - 1; j >= 0; j--)
	{
		B[C[A[j].b[i]] - 1] = A[j];
		C[A[j].b[i]]--;;
	}

	delete[] A;
	delete[] C;
}

void radixSort(U* numbers, int size)
{
	for (int i = 0; i < 3; i++)
		countingSort(numbers, size, i);
}

int main()
{
	std::fstream fin;
	fin.open("input.txt", std::ios::in);

	int length = 0;

	if (fin.is_open())
		fin >> length;

	U* u = new U[length];

	readArray(u, length, fin);
	radixSort(u, length);
	writeArray(u, length);

	delete[] u;
}