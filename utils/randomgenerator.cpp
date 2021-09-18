#include "randomgenerator.hpp"

std::default_random_engine RandomGenerator::random_engine = std::default_random_engine();

RandomGenerator::RandomGenerator() {}

int RandomGenerator::random()
{
    return this->random_engine();
}

bool RandomGenerator::randomBool()
{
    return std::uniform_int_distribution<int>(0, 1)(random_engine);
}

template<typename T>
T RandomGenerator::random_between(T min, T max)
{
    std::uniform_int_distribution<T> uniform_dist(min, max);
    return uniform_dist(random_engine);
}

template int RandomGenerator::random_between<int>(int min, int max);
