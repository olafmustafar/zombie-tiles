#pragma once

#include <random>

class RandomGenerator {
public:
    RandomGenerator();
    int random();

    bool randomBool();

    template <typename T>
    static T random_between(T min, T max);

private:
    static std::default_random_engine random_engine;
};
