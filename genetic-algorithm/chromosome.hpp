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
