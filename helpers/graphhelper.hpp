#pragma once

#include <models/graph.hpp>

class GraphHelper {
public:
    static int diameter_of(const Graph& graph);
    static double average_degree_of(const Graph& graph);
    static std::vector<std::vector<int>> distances_of(const Graph& graph);
};
