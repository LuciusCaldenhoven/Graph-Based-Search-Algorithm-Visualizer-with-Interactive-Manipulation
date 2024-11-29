#include "render.h"

void drawGraph(const Graph& graph) {
    const auto& activeNodes = graph.getActiveNodes();
    const auto& pathNodes = graph.getPathNodes();
    int gridSize = activeNodes.size();

    const float NODE_SPACING = 2.0f / gridSize;
    const float OFFSET = NODE_SPACING / 2.0f - 1.0f;

    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw edges
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (!activeNodes[i][j]) continue;

            float x = i * NODE_SPACING + OFFSET;
            float y = j * NODE_SPACING + OFFSET;

            if (i < gridSize - 1 && activeNodes[i + 1][j]) {
                glBegin(GL_LINES);
                glVertex2f(x, y);
                glVertex2f(x + NODE_SPACING, y);
                glEnd();
            }
            if (j < gridSize - 1 && activeNodes[i][j + 1]) {
                glBegin(GL_LINES);
                glVertex2f(x, y);
                glVertex2f(x, y + NODE_SPACING);
                glEnd();
            }
        }
    }

    // Draw nodes
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (!activeNodes[i][j]) continue;

            float x = i * NODE_SPACING + OFFSET;
            float y = j * NODE_SPACING + OFFSET;

            glBegin(GL_POINTS);
            if (graph.startNode == std::make_pair(i, j)) {
                glColor3f(0.0f, 0.0f, 1.0f);
            } else if (graph.endNode == std::make_pair(i, j)) {
                glColor3f(1.0f, 0.0f, 0.0f);
            } else if (pathNodes[i][j]) {
                glColor3f(0.0f, 1.0f, 0.0f);
            } else {
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            glVertex2f(x, y);
            glEnd();
        }
    }
}
