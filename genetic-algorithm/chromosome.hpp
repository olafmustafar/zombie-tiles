#pragma once

#include <string>

using namespace std;

class Chromosome {
public:
    virtual ~Chromosome();
    virtual void randomize() = 0;
    virtual void mutate() = 0;
    virtual void crossover(Chromosome* other) = 0;
    virtual string to_string() const = 0;
};

//template <typename T>
//class Chromo : public Chromosome {
//    virtual T* crossover(T* other) { }

//    Chromosome* crossover(Chromosome* other) const override
//    {
//        T* chromosome = static_cast<T*>(other);
//        return crossover(chromosome);
//    }
//};
