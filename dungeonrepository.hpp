#pragma once

#include <models/dungeon.hpp>
#include <string>

namespace DungeonRepository {
Dungeon* load(const std::string& path);
void save(const Dungeon& dungeon, const std::string& path);
};
