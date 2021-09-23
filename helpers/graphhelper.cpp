#include "graphhelper.hpp"
#include <iostream>
#include <vector>
using namespace std;

int GraphHelper::diameter_of(const Graph& graph)
{
    const size_t size = graph.size();

    int distances[size][size] {};

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            distances[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < size; ++k) {

        for (int i = 0; i < size; ++i) {
            if (distances[i][k] != -1) {
                for (int j = 0; j < size; ++j) {
                    if (distances[k][j] != -1 && (distances[i][j] == -1 || distances[i][k] + distances[k][j] < distances[i][j])) {
                        distances[i][j] = distances[i][k] + distances[k][j];
                    }
                }
            }
        }
    }

    int diameter = -1;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (diameter < distances[i][j]) {
                diameter = distances[i][j];
            }
        }
    }

    return diameter;
}