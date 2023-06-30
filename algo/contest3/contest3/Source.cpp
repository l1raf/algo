#include <iostream>

void readField(char** field, int n)
{
	for (int i = 0; i < n; i++)
	{
		field[i] = new char[n];

		for (int j = 0; j < n; j++)
		{
			char c;
			std::cin >> c;
			field[i][j] = c;
		}
	}
}

void printField(char** field, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << field[i][j];
		std::cout << "\n";
	}
}

int getNumberOfX(char** field, int n)
{
	int count = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (field[i][j] == 'X')
				count++;

	return count;
}

int getNumberOfZeros(char** field, int n)
{
	int count = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (field[i][j] == '0')
				count++;

	return count;
}

char** replace(char** field, int n, int pos)
{
	char** newField = new char* [n];

	for (int i = 0; i < n; i++)
	{
		newField[i] = new char[n];

		for (int j = 0; j < n; j++)
		{
			newField[i][j] = field[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = pos; j < n; j += 3)
		{
			if (field[i][j] == 'X')
			{
				newField[i][j] = '0';
			}
		}
		pos = (pos + 2) % 3;
	}

	return newField;
}

int main()
{
	int n;
	std::cin >> n;

	char** field = new char* [n];
	readField(field, n);

	int max = getNumberOfX(field, n) / 3;
	char** newField = replace(field, n, 0);

	for (int i = 1; i < 3; i++)
		if (getNumberOfZeros(newField, n) > max)
			newField = replace(field, n, i);

	printField(newField, n);

	for (int i = 0; i < n; i++)
	{
		delete[] newField[i];
		delete[] field[i];
	}
	delete[] newField;
	delete[] field;
}