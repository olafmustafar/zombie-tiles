#include "dungeonrepository.hpp"
#include "libs/json.hpp"
#include <fstream>
#include <iostream>
#include <models/room.hpp>

namespace {
constexpr const char* X = "x";
constexpr const char* Y = "y";
constexpr const char* PLACEMENT_TYPE = "placement_type";
constexpr const char* ROOMS = "rooms";
constexpr const char* HEIGHT = "height";
constexpr const char* WIDTH = "width";
constexpr const char* ENEMIES = "enemies";
constexpr const char* POSITION = "position";
constexpr const char* HEALTH = "health";
constexpr const char* DAMAGE = "damage";
constexpr const char* ATTACK_COOLDOWN = "attack_cooldown";
constexpr const char* VELOCITY = "velocity";
}

Dungeon* DungeonRepository::load(const string& path)
{
    using nlohmann::json;

    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr << "Couldn't load file " << path << "!\n";
        return nullptr;
    }

    json j = json::parse(ifs);

    const size_t w = j[WIDTH];
    const size_t h = j[HEIGHT];

    Dungeon* d = new Dungeon(w, h);

    std::vector<json> rooms = j[ROOMS];
    for (json room_json : rooms) {
        d->add_room({ room_json[X],
                      room_json[Y],
                      room_json[WIDTH],
                      room_json[HEIGHT],
                      room_json[PLACEMENT_TYPE] == "T"
                          ? Room::PlacementType::T
                          : Room::PlacementType::U });
    }

    std::vector<json> enemies = j[ENEMIES];
    for (json enemy_json : enemies) {
        json position_json = enemy_json[POSITION];
        d->add_enemy({ Point { position_json[X].get<int>(),
                               position_json[Y].get<int>() },
                       enemy_json[HEALTH],
                       enemy_json[DAMAGE],
                       enemy_json[ATTACK_COOLDOWN],
                       enemy_json[VELOCITY] });
    }

    ifs.close();

    return d;
}

void DungeonRepository::save(const Dungeon& dungeon, const string& path)
{
    using json = nlohmann::ordered_json;

    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        std::cerr << "Couldn't create file " << path << "!\n";
        return;
    }

    std::vector<json> rooms;
    rooms.reserve(dungeon.rooms().size());
    for (const Room& r : dungeon.rooms()) {
        rooms.push_back({ { X, r.x },
                          { Y, r.y },
                          { WIDTH, r.width },
                          { HEIGHT, r.height },
                          { PLACEMENT_TYPE, (r.placement_type == Room::PlacementType::T) ? "T" : "U" } });
    }

    std::vector<json> enemies;
    enemies.reserve(dungeon.enemies().size());
    for (const Enemy& e : dungeon.enemies()) {
        enemies.push_back(
            { { POSITION, { { X, e.position.x }, { Y, e.position.y } } },
              { HEALTH, e.health },
              { DAMAGE, e.damage },
              { ATTACK_COOLDOWN, e.attackCooldown },
              { VELOCITY, e.velocity } });
    }

    json j = { { WIDTH, dungeon.width() },
               { HEIGHT, dungeon.height() },
               { ROOMS, rooms },
               { ENEMIES, enemies } };

    ofs << j.dump(2);
    ofs.close();
}
