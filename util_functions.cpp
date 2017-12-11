#include "util_functions.h"

int random_int(int lower, int higher)
{

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(lower, higher);
	return dist(mt);

}

float random_float(float lower, float higher)
{

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(lower, higher);
	return dist(mt);

}
