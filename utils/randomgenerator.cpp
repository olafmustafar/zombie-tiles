#include "randomgenerator.hpp"
std::default_random_engine Random::random_engine = std::default_random_engine(0123456);

Random::Random() { }

void Random::set_seed(int seed)
{
    random_engine.seed(seed);
}

int Random::random()
{
    return this->random_engine();
}

bool Random::random_bool(float chance)
{
    return random_between(0.0, 1.0) < chance;
}

template <>
double Random::random_between<double>(double min, double max)
{
    std::uniform_real_distribution<double> uniform_dist(min, max);
    return uniform_dist(random_engine);
}
