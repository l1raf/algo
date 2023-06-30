//У Белоснежки очень много гномов, она даже не знает сколько.
//И все гномы разного роста, но Белоснежка знает, что рост каждого гнома не менее 100 и не более 150 сантиметров.
//Сегодня Белоснежка хочет узнать рост самого высокого и второго по росту гнома.
//Напишите программу, которая поможет ей узнать эту информацию.

#include <iostream>
#include <vector>

int main()
{
	std::vector<int> dwarfs;
	int input;

	std::cin >> input;

	while (input != 0)
	{
		if (input < 100 || input > 150)
		{
			std::cout << "Incorrect number" << std::endl;
			std::cin >> input;
			continue;
		}

		if (dwarfs.size() > 1)
		{
			if (input > dwarfs[0])
			{
				dwarfs[1] = dwarfs[0];
				dwarfs[0] = input;
			}
			else if (input > dwarfs[1]) 
			{
				dwarfs[1] = input;
			}
		}
		else 
		{
			dwarfs.push_back(input);

			if (dwarfs.size() == 2 && dwarfs[0] < dwarfs[1])
			{
				int temp = dwarfs[0];
				dwarfs[0] = dwarfs[1];
				dwarfs[1] = temp;
			}
		}

		std::cin >> input;
	}

	if (dwarfs.size() > 1)
	{
		std::cout << dwarfs[0] << std::endl;
		std::cout << dwarfs[1] << std::endl;
	}
}