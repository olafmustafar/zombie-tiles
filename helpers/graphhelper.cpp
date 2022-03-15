#include "graphhelper.hpp"
#include <iostream>
#include <vector>
using namespace std;

std::vector<std::vector<int>> GraphHelper::distances_of(const Graph& graph)
{
    const size_t size = graph.size();

    std::vector<std::vector<int>> distances { size, std::vector<int>(size, -1) };

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            distances[i][j] = graph[i][j];
        }
    }

    // dikstra
    for (size_t k = 0; k < size; ++k) {
        for (size_t i = 0; i < size; ++i) {
            if (distances[i][k] != -1) {
                for (size_t j = 0; j < size; ++j) {
                    if (distances[k][j] != -1 && (distances[i][j] == -1 || distances[i][k] + distances[k][j] < distances[i][j])) {
                        distances[i][j] = distances[i][k] + distances[k][j];
                    }
                }
            }
        }
    }

    return distances;
}

int GraphHelper::diameter_of(const Graph& graph)
{
    const size_t size = graph.size();

    auto distances = distances_of(graph);

    int diameter = -1;

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (diameter < distances[i][j]) {
                diameter = distances[i][j];
            }
        }
    }

    return diameter;
}

double GraphHelper::average_degree_of(const Graph& graph)
{
    double total = 0.00;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph[i].size(); ++j) {
            if (i != j && graph[i][j] != -1) {
                total += 1.00;
            }
        }
    }
    return total / graph.size();
}
