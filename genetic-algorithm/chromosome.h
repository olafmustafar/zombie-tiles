#pragma once

class Chromosome
{
public:
    virtual ~Chromosome();
    virtual void randomize() = 0;
    virtual void mutate() = 0;
    virtual Chromosome *crossover() const;
};

