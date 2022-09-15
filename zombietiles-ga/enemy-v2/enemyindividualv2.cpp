#include "enemyindividualv2.hpp"
#include "enemychromosomev2.hpp"
#include "models/enemiesconfig.hpp"
#include "models/enemy.hpp"
#include "models/enemypool.hpp"
#include "utils/randomgenerator.hpp"
#include "utils/singleton.hpp"
#include <iostream>

namespace V2 {

double EnemyIndividual::calculate_fitness()
{
    size_t dungeon_size = St<EnemiesConfig>.current_dungeon->rooms().size();
    EnemyChromosome* chrom = get_chromosome();

    std::vector<int> att_sums = std::vector(dungeon_size, 0);
    for (size_t i = 0; i < chrom->genes().size(); i++) {
        int gene = chrom->genes()[i];
        if (gene == -1) {
            continue;
        }

        att_sums[gene] += sum_att(St<EnemyPool>[i]);
    }

    const double desired = (St<EnemiesConfig>.max_att * 2) * St<EnemiesConfig>.enemy_count_by_room;
    log_data.desired_diff = std::vector(dungeon_size, 0);

    double fitness = 0;
    int i = 0;
    for (int att_sum : att_sums) {
        fitness += att_sum < desired ? desired - att_sum : att_sum - desired;
        log_data.desired_diff[i++] = att_sum < desired ? desired - att_sum : att_sum - desired;
    }

    fitness = ((dungeon_size * desired) - fitness) / (dungeon_size * desired);

    return fitness;
}

inline int EnemyIndividual::sum_att(const Enemy& enemy)
{
    return enemy.damage + enemy.health + enemy.velocity + enemy.attackCooldown;
}

string EnemyIndividual::to_string() const { return ""; }

void EnemyIndividual::report() const
{
    std::cout << "room_sum: [";
    for (auto room_sum : log_data.desired_diff) {
        std::cout << room_sum << ", ";
    }
    std::cout << "]\ngenes: [";
    for (auto gene : get_chromosome()->genes()) {
        std::cout << gene << ", ";
    }
    std::cout << "]\n";
}

std::vector<Enemy> EnemyIndividual::to_enemies(const DungeonMatrix& dm) const
{
    std::vector<Enemy> enemies = {};

    std::vector<std::vector<Point>> positions_per_room = { St<EnemiesConfig>.current_dungeon->rooms().size(), std::vector<Point> {} };

    for (size_t x = 0; x < dm.width(); x++) {
        for (size_t y = 0; y < dm.height(); y++) {
            Point pos = { x, y };
            if (dm[pos] == DungeonMatrix::EMPTY) {
                continue;
            }
            positions_per_room[dm[pos]].push_back(pos);
        }
    }

    std::unordered_set<Point> used_positions {};
    for (size_t i = 0; i < St<EnemyPool>.size(); i++) {
        int gene = get_chromosome()->genes()[i];
        if ( gene == -1 || positions_per_room[gene].empty()) {
            continue;
        }

        Point pos = {};
        do {

            if (positions_per_room[gene].empty()) {
                break;
            }
            pos = Random::take_random_element(positions_per_room[gene]);

        } while (used_positions.contains(pos));
        used_positions.insert(pos);

        Enemy enemy { St<EnemyPool>[i] };
        enemy.position = pos;
        enemies.push_back(enemy);
    }

    return enemies;
}

}
