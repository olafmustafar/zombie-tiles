cmake_minimum_required(VERSION 3.14)

project(ZombieTiles LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(ZombieTiles SHARED
  ZombieTiles_global.h
  zombietiles.h
  zombietiles.cpp
  tilemap.h
  tilemap.cpp
  tiletexture.h
  tiletexture.cpp
  tile.h
  tile.cpp
  genetic-algorithm/geneticalgorithm.h
  genetic-algorithm/geneticalgorithm.cpp
  genetic-algorithm/individual.h
  genetic-algorithm/individual.cpp
  genetic-algorithm/gene.h
  genetic-algorithm/gene.cpp
  zombie-tiles-ga/zombietilesag.h
  zombie-tiles-ga/zombietilesag.cpp
  zombie-tiles-ga/zombietilesindividual.h
  zombie-tiles-ga/zombietilesindividual.cpp
)

set_target_properties(ZombieTiles PROPERTIES PUBLIC_HEADER "zombietiles.h;ZombieTiles_global.h;")
install( TARGETS ZombieTiles DESTINATION "${CMAKE_BINARY_DIR}/lib" )
install( FILES zombietiles.h DESTINATION "${CMAKE_BINARY_DIR}/include" )
#message( STATUS "${CMAKE_INSTALL_PREFIX}" )
#message( STATUS "${CMAKE_BINARY_DIR}" )

target_include_directories(ZombieTiles PRIVATE .)

target_link_libraries(ZombieTiles PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(ZombieTiles PRIVATE ZOMBIETILES_LIBRARY)


