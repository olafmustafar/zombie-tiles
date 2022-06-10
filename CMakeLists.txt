cmake_minimum_required(VERSION 3.14)

project(zombietiles LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)
add_compile_options(-Wall -Wextra -pedantic)
 
add_library(zombietiles SHARED
  zombietiles_global.hpp
  zombietiles.hpp
  zombietiles.cpp
  dungeonrepository.hpp
  dungeonrepository.cpp
  libs/json.hpp
  utils/randomgenerator.hpp
  utils/randomgenerator.cpp
  utils/logger.hpp
  utils/logger.cpp
  utils/singleton.hpp
  models/dungeonmatrix.hpp
  models/dungeonmatrix.cpp
  models/dungeonconfig.hpp
  models/dungeonconfig.cpp
  models/enemiesconfig.hpp
  models/enemiesconfig.cpp
  models/dungeon.hpp
  models/dungeon.cpp
  models/direction.hpp
  models/direction.cpp
  models/room.hpp
  models/room.cpp
  models/graph.hpp
  models/line.hpp
  models/line.cpp
  models/wall.hpp
  models/point.hpp
  models/point.cpp
  models/door.hpp
  models/door.cpp
  models/entity.hpp
  models/entity.cpp
  models/enemy.hpp
  models/enemy.cpp
  helpers/dungeonmatrixhelper.hpp
  helpers/dungeonmatrixhelper.cpp
  helpers/roommaphelper.hpp
  helpers/roommaphelper.cpp
  helpers/roomhelper.hpp
  helpers/roomhelper.cpp
  helpers/graphhelper.hpp
  helpers/graphhelper.cpp
  genetic-algorithm/geneticalgorithm.hpp
  genetic-algorithm/geneticalgorithm.cpp
  genetic-algorithm/individual.hpp
  genetic-algorithm/individual.cpp
  genetic-algorithm/chromosome.hpp
  genetic-algorithm/chromosome.cpp
  zombietiles-ga/dungeon/zombietilesga.hpp
  zombietiles-ga/dungeon/zombietilesga.cpp
  zombietiles-ga/dungeon/zombietilesindividual.hpp
  zombietiles-ga/dungeon/zombietilesindividual.cpp
  zombietiles-ga/dungeon/zombietileschromosome.hpp
  zombietiles-ga/dungeon/zombietileschromosome.cpp
  zombietiles-ga/dungeon/roomgene.hpp
  zombietiles-ga/dungeon/roomgene.cpp
  zombietiles-ga/enemy/enemyindividual.h
  zombietiles-ga/enemy/enemyindividual.cpp
  zombietiles-ga/enemy/enemychormosome.h
  zombietiles-ga/enemy/enemychormosome.cpp
)

set_target_properties(zombietiles PROPERTIES PUBLIC_HEADER "zombietiles.hpp;zombietiles_global.hpp;")
INSTALL(TARGETS zombietiles
        LIBRARY DESTINATION "${CMAKE_BINARY_DIR}/lib"
        PUBLIC_HEADER DESTINATION "${CMAKE_BINARY_DIR}/include"
)

INSTALL( DIRECTORY "./models" DESTINATION "${CMAKE_BINARY_DIR}/include"
    FILES_MATCHING PATTERN "*.hpp" )

target_include_directories(zombietiles PRIVATE .)

target_compile_definitions(zombietiles PRIVATE ZOMBIETILES_LIBRARY)


