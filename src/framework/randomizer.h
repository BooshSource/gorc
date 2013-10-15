#pragma once

#include <random>

namespace gorc {

class randomizer {
private:
	std::default_random_engine rng;

public:
	randomizer();

	inline operator double() {
		return std::generate_canonical<double, 10>(rng);
	}
};

}
