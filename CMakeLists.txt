cmake_minimum_required(VERSION 3.14)

project(zombietiles LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(zombietiles SHARED
  zombietiles_global.h
  zombietiles.h
  zombietiles.cpp
  utils/randomgenerator.h
  utils/randomgenerator.cpp
  utils/logger.h
  utils/logger.cpp
  models/dungeonconfig.h
  models/dungeonconfig.cpp
  models/tilemap.h
  models/tilemap.cpp
  models/room.h
  models/room.cpp
  helpers/tilemaphelper.h
  helpers/tilemaphelper.cpp
  helpers/roomhelper.h
  helpers/roomhelper.cpp
  genetic-algorithm/geneticalgorithm.h
  genetic-algorithm/geneticalgorithm.cpp
  genetic-algorithm/individual.h
  genetic-algorithm/individual.cpp
  genetic-algorithm/chromosome.h
  genetic-algorithm/chromosome.cpp
  zombietiles-ga/zombietilesga.h
  zombietiles-ga/zombietilesga.cpp
  zombietiles-ga/zombietilesindividual.h
  zombietiles-ga/zombietilesindividual.cpp
  zombietiles-ga/zombietileschromosome.h
  zombietiles-ga/zombietileschromosome.cpp
  zombietiles-ga/roomgene.h
  zombietiles-ga/roomgene.cpp
)

set_target_properties(zombietiles PROPERTIES PUBLIC_HEADER "zombietiles.h;zombietiles_global.h;")
INSTALL(TARGETS zombietiles
        LIBRARY DESTINATION "${CMAKE_BINARY_DIR}/lib"
        PUBLIC_HEADER DESTINATION "${CMAKE_BINARY_DIR}/include"
)

target_include_directories(zombietiles PRIVATE .)

#target_link_libraries(zombietiles PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(zombietiles PRIVATE ZOMBIETILES_LIBRARY)


