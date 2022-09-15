#pragma once

#include "enemychromosomev2.hpp"
#include <cstdint>
#include <genetic-algorithm/individual.hpp>
#include <models/enemiesconfig.hpp>
#include <models/enemiesmetadata.hpp>
#include <vector>

namespace V2 {

struct EnemyIndividual : Individual<EnemyChromosome> {
    string to_string() const override;
    void report() const override;
    std::vector<Enemy> to_enemies(const DungeonMatrix& dm) const;

private:
    double calculate_fitness() override;
    inline static int sum_att(const Enemy& enemy);

    struct LogData {
        std::vector<int> desired_diff;
    } log_data;

};

}
