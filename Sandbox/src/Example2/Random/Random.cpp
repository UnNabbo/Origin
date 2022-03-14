#include "Random.h"

int randomInt(int x, int y) {
	std::random_device os_seed;
	const uint_least32_t seed = os_seed();

	std::mt19937 generator(seed);
	std::uniform_int_distribution< uint_least32_t > distribute(x, y);

	return distribute(generator);
}
