#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

// Функция сортировки подсчетом
void countingSort(int* numbers, int array_size)
{
	int max = numbers[0];
	int* B = new int[array_size];

	for (int i = 0; i < array_size; i++)
		if (numbers[i] > max)
			max = numbers[i];

	int k = max + 1;

	//Вспомогательный массив
	int* C = new int[k];

	for (int i = 0; i < k; i++)
		C[i] = 0;

	for (int i = 0; i < array_size; i++)
		C[numbers[i]]++;

	for (int i = 1; i < k; i++)
		C[i] += C[i - 1];

	for (int i = array_size - 1; i >= 0; i--)
	{
		B[C[numbers[i]] - 1] = numbers[i];
		C[numbers[i]]--;
	}

	for (int i = 0; i < array_size; i++)
		numbers[i] = B[i];

	delete[] B;
	delete[] C;
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
	countingSort(brr, n);

	//Запись в файл
	rw.writeArray(brr, n);

	//освобождаем память
	delete[] brr;

	return 0;
}
