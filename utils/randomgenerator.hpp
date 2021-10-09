#pragma once

#include <random>

class RandomGenerator {
public:
    RandomGenerator();
    int random();

    bool randomBool();

    template <typename T>
    static T random_between(T min, T max)
    {
        std::uniform_int_distribution<T> uniform_dist(min, max);
        return uniform_dist(random_engine);
    }

private:
    static std::default_random_engine random_engine;
};

template <>
double RandomGenerator::random_between(double min, double max);
