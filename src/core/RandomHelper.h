#pragma once

#include <random>

class RandomHelper
{
public:
	static unsigned int SEED; // Seed for the random number generator

	// Returns a random float between min and max
	static float GetRandomFloat(float min, float max)
	{
		static std::default_random_engine engine(SEED);
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(engine);
	}

	// Returns a random integer between min and max
	static int GetRandomInt(int min, int max)
	{
		static std::default_random_engine engine(SEED);
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(engine);
	}
};