#pragma once

#include "enemychormosome.h"
#include <genetic-algorithm/individual.hpp>
#include <models/enemiesmetadata.hpp>
#include <models/enemiesconfig.hpp>

struct EnemyIndividual : Individual<EnemyChormosome> {
    EnemyIndividual();
    void crossover(IndividualImpl* other) override;
    void mutate() override;
    string to_string() const override;
    void report() const override;

private:
    const EnemiesConfig& enemies_config;
    EnemiesMetadata m_metadata;
    uint32_t min_att;
    uint32_t max_att;

    double calculate_fitness() override;

    double position_fitness(const EnemiesMetadata& metadata) const;
    double atributes_balance_fitness(const EnemiesMetadata& metadata) const;
};
