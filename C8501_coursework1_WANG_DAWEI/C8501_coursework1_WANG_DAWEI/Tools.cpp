#include "Tools.h"

int maze1::Tools::getRamdom(int min, int max) {
	std::uniform_int_distribution<> die{ min, max };
	return die(mersenne);
}
