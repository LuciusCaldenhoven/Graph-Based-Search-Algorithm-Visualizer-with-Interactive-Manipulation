#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

class Graph {
public:
    Graph(int gridSize, float deletePercentage, std::pair<int, int> startNode, std::pair<int, int> endNode);

    void initializeActiveNodes();
    const std::vector<std::vector<bool>>& getActiveNodes() const;
    const std::vector<std::vector<bool>>& getPathNodes() const;

    std::pair<int, int> startNode;
    std::pair<int, int> endNode;

private:
    int gridSize;
    float deletePercentage;
    std::vector<std::vector<bool>> activeNodes;
    std::vector<std::vector<bool>> pathNodes;
};

#endif
