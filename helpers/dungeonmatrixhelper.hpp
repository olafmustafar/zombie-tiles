#pragma once
#include <cstdint>
#include <models/dungeonmatrix.hpp>

namespace DungeonMatrixHelper {
size_t narrow_rooms_of(const DungeonMatrix& dm);
size_t tiny_rooms_of(const DungeonMatrix& dm);
size_t rooms_count_of(const DungeonMatrix& dm);
}
