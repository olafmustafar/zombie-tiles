#pragma once

#include "enemychormosome.h"
#include <cstdint>
#include <genetic-algorithm/individual.hpp>
#include <models/enemiesconfig.hpp>
#include <models/enemiesmetadata.hpp>
#include <vector>

struct EnemyGeneMetadata {
    bool is_allocated;
    double dmg_hlt_diff;
    double cdw_vlt_diff;
    double d, h, c, v;
};

struct EnemieGenesMetadata {
    EnemiesConfig enemies_config;
    std::vector<EnemyGeneMetadata> enemy_metadata;
    std::vector<uint32_t> total_att_by_room;
    std::vector<size_t> enemy_count_by_room;
};

struct EnemyIndividual : Individual<EnemyChormosome> {
    EnemyIndividual();
    void crossover(IndividualImpl* other) override;
    void mutate() override;
    string to_string() const override;
    void report() const override;

private:
    const EnemiesConfig& enemies_config;
    EnemieGenesMetadata m_metadata;
    uint32_t min_att;
    uint32_t max_att;

    double calculate_fitness() override;

    double position_fitness(const EnemieGenesMetadata& metadata) const;
    double atributes_balance_fitness(const EnemieGenesMetadata& metadata) const;
    EnemieGenesMetadata calculate_enemie_genes_metadata(const EnemiesConfig& enemies_config, const std::vector<EnemyGene>& genes);
};
