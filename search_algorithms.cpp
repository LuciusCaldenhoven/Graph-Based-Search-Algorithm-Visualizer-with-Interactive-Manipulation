#include "search_algorithms.h"
#include <queue>
#include <cmath>
#include <limits>

// Helper function for heuristic calculation (used in A* and Hill Climbing)
int heuristic(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

// Executes the selected search algorithm
void runSearch(Graph& graph, int selectedAlgorithm) {
    switch (selectedAlgorithm) {
        case 1:
            if (!DFS(graph)) std::cout << "No valid path found.\n";
            else std::cout << "Path found.\n";
            break;
        case 2:
            if (!BFS(graph)) std::cout << "No valid path found.\n";
            else std::cout << "Path found.\n";
            break;
        case 3:
            if (!AStar(graph)) std::cout << "No valid path found.\n";
            else std::cout << "Path found.\n";
            break;
        case 4:
            if (!HillClimbing(graph)) std::cout << "No valid path found.\n";
            else std::cout << "Path found.\n";
            break;
        default:
            std::cout << "Invalid option.\n";
            break;
    }
}

// Depth-First Search (DFS)
bool DFS(Graph& graph) {
    auto& activeNodes = graph.getActiveNodes();
    auto& pathNodes = graph.getPathNodes();
    std::vector<std::vector<bool>> visited(graph.getActiveNodes().size(), std::vector<bool>(graph.getActiveNodes().size(), false));

    std::function<bool(std::pair<int, int>)> dfsHelper = [&](std::pair<int, int> node) {
        if (node == graph.endNode) {
            pathNodes[node.first][node.second] = true;
            return true;
        }

        int x = node.first, y = node.second;
        if (x < 0 || x >= activeNodes.size() || y < 0 || y >= activeNodes.size() || !activeNodes[x][y] || visited[x][y]) {
            return false;
        }

        visited[x][y] = true;

        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto& dir : directions) {
            if (dfsHelper({x + dir.first, y + dir.second})) {
                pathNodes[x][y] = true;
                return true;
            }
        }
        return false;
    };

    return dfsHelper(graph.startNode);
}

// Breadth-First Search (BFS)
bool BFS(Graph& graph) {
    auto& activeNodes = graph.getActiveNodes();
    auto& pathNodes = graph.getPathNodes();
    std::vector<std::vector<bool>> visited(graph.getActiveNodes().size(), std::vector<bool>(graph.getActiveNodes().size(), false));
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<std::pair<int, int>>> predecessor(activeNodes.size(), std::vector<std::pair<int, int>>(activeNodes.size(), {-1, -1}));

    q.push(graph.startNode);
    visited[graph.startNode.first][graph.startNode.second] = true;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current == graph.endNode) {
            // Reconstruct path
            for (auto at = graph.endNode; at != graph.startNode; at = predecessor[at.first][at.second]) {
                pathNodes[at.first][at.second] = true;
            }
            pathNodes[graph.startNode.first][graph.startNode.second] = true;
            return true;
        }

        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto& dir : directions) {
            int nx = current.first + dir.first;
            int ny = current.second + dir.second;

            if (nx >= 0 && nx < activeNodes.size() && ny >= 0 && ny < activeNodes.size() && !visited[nx][ny] && activeNodes[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
                predecessor[nx][ny] = current;
            }
        }
    }

    return false;
}

// A* Search
bool AStar(Graph& graph) {
    auto& activeNodes = graph.getActiveNodes();
    auto& pathNodes = graph.getPathNodes();

    struct Node {
        std::pair<int, int> position;
        int gCost;
        int fCost;
        std::pair<int, int> predecessor;
        bool operator<(const Node& other) const {
            return fCost > other.fCost; // Min-heap
        }
    };

    std::priority_queue<Node> pq;
    std::vector<std::vector<int>> gCost(activeNodes.size(), std::vector<int>(activeNodes.size(), std::numeric_limits<int>::max()));
    std::vector<std::vector<bool>> visited(activeNodes.size(), std::vector<bool>(activeNodes.size(), false));
    std::vector<std::vector<std::pair<int, int>>> predecessor(activeNodes.size(), std::vector<std::pair<int, int>>(activeNodes.size(), {-1, -1}));

    gCost[graph.startNode.first][graph.startNode.second] = 0;
    pq.push({graph.startNode, 0, heuristic(graph.startNode, graph.endNode), {-1, -1}});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited[current.position.first][current.position.second]) continue;
        visited[current.position.first][current.position.second] = true;

        if (current.position == graph.endNode) {
            // Reconstruct path
            for (auto at = graph.endNode; at != graph.startNode; at = predecessor[at.first][at.second]) {
                pathNodes[at.first][at.second] = true;
            }
            pathNodes[graph.startNode.first][graph.startNode.second] = true;
            return true;
        }

        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto& dir : directions) {
            int nx = current.position.first + dir.first;
            int ny = current.position.second + dir.second;

            if (nx >= 0 && nx < activeNodes.size() && ny >= 0 && ny < activeNodes.size() && activeNodes[nx][ny]) {
                int tentativeGCost = gCost[current.position.first][current.position.second] + 1;

                if (tentativeGCost < gCost[nx][ny]) {
                    gCost[nx][ny] = tentativeGCost;
                    pq.push({{nx, ny}, tentativeGCost, tentativeGCost + heuristic({nx, ny}, graph.endNode), current.position});
                    predecessor[nx][ny] = current.position;
                }
            }
        }
    }

    return false;
}

// Hill Climbing
bool HillClimbing(Graph& graph) {
    auto& activeNodes = graph.getActiveNodes();
    auto& pathNodes = graph.getPathNodes();

    std::pair<int, int> current = graph.startNode;
    pathNodes[current.first][current.second] = true;

    while (current != graph.endNode) {
        std::pair<int, int> bestNeighbor = {-1, -1};
        int minHeuristic = std::numeric_limits<int>::max();

        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto& dir : directions) {
            int nx = current.first + dir.first;
            int ny = current.second + dir.second;

            if (nx >= 0 && nx < activeNodes.size() && ny >= 0 && ny < activeNodes.size() && activeNodes[nx][ny]) {
                int h = heuristic({nx, ny}, graph.endNode);
                if (h < minHeuristic) {
                    minHeuristic = h;
                    bestNeighbor = {nx, ny};
                }
            }
        }

        if (bestNeighbor.first == -1) return false; // No valid neighbor
        current = bestNeighbor;
        pathNodes[current.first][current.second] = true;
    }

    return true;
}
