#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "graph.h"

void runSearch(Graph& graph, int selectedAlgorithm);
bool DFS(Graph& graph);
bool BFS(Graph& graph);
bool AStar(Graph& graph);
bool HillClimbing(Graph& graph);

#endif
