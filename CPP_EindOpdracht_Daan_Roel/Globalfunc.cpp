#include "stdafx.h"
#include "Globalfunc.h"
#include <string>
#include <sstream>
#include <iostream>

int getRandom(int min, int max)
{
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	auto random_integer = uni(rng);
	return random_integer;
}

int getAnswer(int amountOfOptions) {
	std::string line;
	double d;
	int answer = -1;
	while (getline(std::cin, line))
	{
		std::stringstream ss(line);
		if (ss >> d)
		{
			if (ss.eof())
			{
				answer = std::stoi(line);
				if (answer < amountOfOptions && answer >= 0) {
					break;
				}
			}
		}
		std::cout << "invalid input, try again" << std::endl;
	}
	return answer;
}