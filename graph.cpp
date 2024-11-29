#include "graph.h"
#include <cstdlib>
#include <ctime>

Graph::Graph(int gridSize, float deletePercentage, std::pair<int, int> startNode, std::pair<int, int> endNode)
    : gridSize(gridSize), deletePercentage(deletePercentage), startNode(startNode), endNode(endNode) {}

void Graph::initializeActiveNodes() {
    activeNodes.resize(gridSize, std::vector<bool>(gridSize, true));
    int nodesToDelete = static_cast<int>(gridSize * gridSize * (deletePercentage / 100.0));

    srand(static_cast<unsigned int>(time(nullptr)));

    while (nodesToDelete > 0) {
        int i = rand() % gridSize;
        int j = rand() % gridSize;
        if ((i == startNode.first && j == startNode.second) || 
            (i == endNode.first && j == endNode.second)) {
            continue;
        }
        if (activeNodes[i][j]) {
            activeNodes[i][j] = false;
            --nodesToDelete;
        }
    }
}

const std::vector<std::vector<bool>>& Graph::getActiveNodes() const {
    return activeNodes;
}

const std::vector<std::vector<bool>>& Graph::getPathNodes() const {
    return pathNodes;
}
