#include <GLFW/glfw3.h>
#include <iostream>
#include "graph.h"
#include "render.h"
#include "search_algorithms.h"

int gridSize; 
float deletePercentage; 
int selectedAlgorithm;

std::pair<int, int> startNode;    
std::pair<int, int> endNode;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        int gridX = static_cast<int>(gridSize * xpos / width);
        int gridY = gridSize - 1 - static_cast<int>(gridSize * ypos / height);

        static bool selectingStartNode = true;
        if (selectingStartNode) {
            startNode = {gridX, gridY};
            std::cout << "Start node selected at: " << gridX << ", " << gridY << std::endl;
        } else {
            endNode = {gridX, gridY};
            std::cout << "End node selected at: " << gridX << ", " << gridY << std::endl;

            Graph graph(gridSize, deletePercentage, startNode, endNode);
            graph.initializeActiveNodes();
            runSearch(graph, selectedAlgorithm);
        }
        selectingStartNode = !selectingStartNode;
    }
}

int main() {
    std::cout << "Enter the grid size (N): ";
    std::cin >> gridSize;
    std::cout << "Enter the percentage of nodes to delete: ";
    std::cin >> deletePercentage;

    std::cout << "Select the search algorithm:\n";
    std::cout << "1. DFS\n2. BFS\n3. A*\n4. Hill Climbing\n";
    std::cin >> selectedAlgorithm;

    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "NxN Grid with Deleted Nodes", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glfwSetMouseButtonCallback(window, mouseButtonCallback); 

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
