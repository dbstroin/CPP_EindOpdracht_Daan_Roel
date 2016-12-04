#include "stdafx.h"
#include "Globalfunc.h"

int getRandom(int min, int max)
{
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	auto random_integer = uni(rng);
	return random_integer;
}
