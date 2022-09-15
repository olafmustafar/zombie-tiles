#pragma once

#include <random>
#include <type_traits>

class Random {
public:
    Random();

    static void set_seed(int seed);
    int random();
    static bool random_bool(float chance = 0.5);

    template <typename T>
    static T random_between(T min, std::type_identity_t<T> max)
    {
        std::uniform_int_distribution<T> uniform_dist(min, max);
        return uniform_dist(random_engine);
    }

    template <typename T>
    static typename T::value_type random_element(const T& list)
    {
        return list[random_between(0, list.size() - 1)];
    }

    template <typename T>
    static typename T::value_type take_random_element(T& list)
    {
        size_t index = random_between(0, list.size() - 1);
        auto element = list[index];
        list.erase(list.cbegin() + index);
        return element;
    }

private:
    static std::default_random_engine random_engine;
};

template <>
double Random::random_between(double min, double max);
