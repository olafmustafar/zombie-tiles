#pragma once

#include <string>
#include "zombietileschromosome.hpp"
#include <genetic-algorithm/individual.hpp>
#include <models/dungeonmetadata.hpp>

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome> {
public:
    void crossover(IndividualImpl* other) override;
    void mutate() override;
    string to_string() const override;
    Dungeon get_map() const;
    void report() const override;
private:
    std::string m_report;
    DungeonMetadata m_metadata;

    double calculate_fitness() override;
};
