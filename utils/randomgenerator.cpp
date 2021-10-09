#include "randomgenerator.hpp"

std::default_random_engine RandomGenerator::random_engine = std::default_random_engine();

RandomGenerator::RandomGenerator() { }

int RandomGenerator::random()
{
    return this->random_engine();
}

bool RandomGenerator::randomBool()
{
    return std::uniform_int_distribution<int>(0, 1)(random_engine);
}

template <>
double RandomGenerator::random_between<double>(double min, double max)
{
    std::uniform_real_distribution<double> uniform_dist(min, max);
    return uniform_dist(random_engine);
}
