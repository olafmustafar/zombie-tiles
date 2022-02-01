#pragma once

#include "enemychormosome.h"
#include <genetic-algorithm/individual.hpp>

class EnemyIndividual : public Individual<EnemyChormosome> {
public:
    EnemyIndividual();
};
