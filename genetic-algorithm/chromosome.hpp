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

template <typename T>
class ChromosomeImpl : public Chromosome {
public:
    void crossover(Chromosome* other) override
    {
        crossover(static_cast<T*>(other));
    }

    virtual void crossover(T* other) = 0;
};
