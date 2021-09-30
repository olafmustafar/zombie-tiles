cmake_minimum_required(VERSION 3.14)

project(zombietiles LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic)
 
add_library(zombietiles SHARED
  zombietiles_global.hpp
  zombietiles.hpp
  zombietiles.cpp
  utils/randomgenerator.hpp
  utils/randomgenerator.cpp
  utils/logger.hpp
  utils/logger.cpp
  models/dungeonconfig.hpp
  models/dungeonconfig.cpp
  models/tilemap.hpp
  models/tilemap.cpp
  models/room.hpp
  models/room.cpp
  models/graph.hpp
  helpers/tilemaphelper.hpp
  helpers/tilemaphelper.cpp
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
  zombietiles-ga/zombietilesga.hpp
  zombietiles-ga/zombietilesga.cpp
  zombietiles-ga/zombietilesindividual.hpp
  zombietiles-ga/zombietilesindividual.cpp
  zombietiles-ga/zombietileschromosome.hpp
  zombietiles-ga/zombietileschromosome.cpp
  zombietiles-ga/roomgene.hpp
  zombietiles-ga/roomgene.cpp
)

set_target_properties(zombietiles PROPERTIES PUBLIC_HEADER "zombietiles.hpp;zombietiles_global.hpp;")
INSTALL(TARGETS zombietiles
        LIBRARY DESTINATION "${CMAKE_BINARY_DIR}/lib"
        PUBLIC_HEADER DESTINATION "${CMAKE_BINARY_DIR}/include"
)

target_include_directories(zombietiles PRIVATE .)

target_compile_definitions(zombietiles PRIVATE ZOMBIETILES_LIBRARY)


