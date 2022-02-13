#pragma once

#include "enemychormosome.h"
#include <genetic-algorithm/individual.hpp>
#include <models/enemiesconfig.hpp>

struct EnemyIndividual : Individual<EnemyChormosome> {
    EnemyIndividual();
    void crossover(IndividualImpl* other) override;
    void mutate() override;
    string to_string() const override;

private:
    const EnemiesConfig& enemies_config;
    uint32_t min_att;
    uint32_t max_att;

    double calculate_fitness() const override;

    double position_fitness(const std::vector<Enemy>& enemies) const;
    double atributes_balance_fitness(const std::vector<Enemy>& enemies) const;
};
