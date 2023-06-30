#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

union U
{
	unsigned int a; // occupies 4 bytes
	unsigned char b[4]; // occupies 4 bytes
};

//Сортировка подсчётом, переделанная под union
void countingSort(int* numbers, int array_size, int i)
{
	int max = 0;
	U* A = new U[array_size];

	for (int j = 0; j < array_size; j++)
	{
		A[j].a = numbers[j];

		if (A[j].b[i] > max)
			max = A[j].b[i];
	}

	int k = max + 1;

	//Вспомогательный массив
	int* C = new int[k];

	for (int j = 0; j < k; j++)
		C[j] = 0;

	for (int j = 0; j < array_size; j++)
		C[A[j].b[i]]++;

	for (int j = 1; j < k; j++)
		C[j] += C[j - 1];

	for (int j = array_size - 1; j >= 0; j--)
	{
		numbers[C[A[j].b[i]] - 1] = A[j].a;
		C[A[j].b[i]]--;;
	}

	delete[] A;
	delete[] C;
}

// Функция цифровой сортировки
void radixSort(int* numbers, int array_size)
{
	for (int i = 0; i < 3; i++)
		countingSort(numbers, array_size, i);
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
	//Объект для работы с файлами
	ReadWriter rw;

	int* brr = nullptr;
	int n;

	//Ввод из файла
	n = rw.readInt();

	brr = new int[n];
	rw.readArray(brr, n);

	//Запуск сортировки, ответ в том же массиве (brr)
	radixSort(brr, n);

	//Запись в файл
	rw.writeArray(brr, n);

	//освобождаем память
	delete[] brr;

	return 0;
}
