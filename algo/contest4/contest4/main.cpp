#include "ReadWriter.h"
//iostream, fstream, Student_and_Ski.h включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных методов для решения задачи.
//Рекомендуется использовать имеющиеся классы Student и Ski для решения задачи.

int skisPartition(Ski* skis, int left, int right, Student pivot)
{
	int i = left;

	for (int j = left; j < right; j++)
	{
		if (compare(pivot, skis[j]) < 0)
		{
			swap(skis[i], skis[j]);
			i++;
		}
		else if (compare(pivot, skis[j]) == 0)
		{
			swap(skis[j], skis[right]);
			j--;
		}
	}

	swap(skis[i], skis[right]);

	return i;
}

int studentsPartition(Student* students, int left, int right, Ski pivot)
{
	int i = left;

	for (int j = left; j < right; j++)
	{
		if (compare(students[j], pivot) > 0)
		{
			std::swap(students[j], students[i]);
			i++;
		}
		else if (compare(students[j], pivot) == 0)
		{
			std::swap(students[j], students[right]);
			j--;
		}
	}

	std::swap(students[i], students[right]);

	return i;
}

//Sorts students by id
void quickSort(Ski* skis, Student* students, int left, int right)
{
	int i = left;
	int j = right;
	Student pivot = students[(i + j) / 2];

	while (i <= j)
	{
		while (students[i].id < pivot.id)
			i++;

		while (students[j].id > pivot.id)
			j--;

		if (i <= j)
		{
			swap(students[i], students[j]);
			swap(skis[i], skis[j]);
			i++;
			j--;
		}
	}

	if (j > left)
		quickSort(skis, students, left, j);

	if (i < right)
		quickSort(skis, students, i, right);
}

void matchStudentsAndSkis(Ski* skis, Student* students, int left, int right)
{
	if (left < right)
	{
		//Using student pivot to partition skis  
		int pivot = skisPartition(skis, left, right, students[(left + right) / 2]);

		//Using ski pivot to partition students
		studentsPartition(students, left, right, skis[pivot]);

		if (pivot > 0)
			matchStudentsAndSkis(skis, students, left, pivot - 1);
		matchStudentsAndSkis(skis, students, pivot + 1, right);
	}
}

//Задача - реализовать этот метод.
//Ответ должен быть упорядочен по возрастанию номеров студентов(!), то есть их id.
//Ответы должны быть в этих же массивах.
void findPairs(Student* students, Ski* skis, int n)
{
	matchStudentsAndSkis(skis, students, 0, n - 1);
	quickSort(skis, students, 0, n - 1);
}

int main()
{
	ReadWriter rw;

	Student* students = nullptr;
	Ski* skis = nullptr;
	int n;

	//Read n from file
	n = rw.readInt();

	//Create arrays
	students = new Student[n];
	skis = new Ski[n];

	//read Students and Skis from file
	rw.readStudents(students, n);
	rw.readSkis(skis, n);

	//Find pairs
	findPairs(students, skis, n);

	//Write answer to file
	rw.writeStudentsAndSkis(students, skis, n);

	delete[] students;
	delete[] skis;
	return 0;
}
