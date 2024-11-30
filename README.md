# Graph-Based-Search-Algorithm-Visualizer-with-Interactive-Manipulation

## **Overview**
This project is a visualizer for graph-based search algorithms, implemented in C++ using OpenGL. It allows users to dynamically create and manipulate a grid-based graph, select start and end nodes, and visualize the execution of various search algorithms interactively.

The primary goal is to help users understand and compare how different pathfinding algorithms traverse a graph to find the shortest path or explore the grid.

---

## **Features**
- Interactive graph manipulation:
  - Select start and end nodes using the mouse.
  - Generate randomized obstacles based on a configurable percentage.
- Visualization of search algorithms:
  - **Depth-First Search (DFS)**
  - **Breadth-First Search (BFS)**
  - **A* Search**
  - **Hill Climbing**
- Real-time rendering using OpenGL for smooth visual feedback.
- Modular code structure for easy extension and maintenance.

---

## **Technologies Used**
- **C++**: Core programming language for implementing algorithms and managing the graph structure.
- **OpenGL**: For rendering the graph and visualizing the algorithms.
- **GLFW**: For window management and handling user inputs.

---

## **How It Works**
1. The program generates an NxN grid graph where each cell represents a node.
2. Users can:
   - Define the **start node** and **end node** interactively.
   - Randomly remove nodes from the graph to simulate obstacles.
3. Once the graph is set, users select a search algorithm to visualize how it navigates from the start node to the end node.
4. The visualization highlights the path found (if any) and nodes explored during the search.


## **Usage**
1. When the program starts, enter the grid size (N) and the percentage of nodes to be removed.
2. Use the following controls:
   - Left Click: Select the start node and end node.
   - Keyboard: Choose the search algorithm.
3. Watch the visualization of the selected algorithm.

## **Search Algorithms Implemented**
1. **Depth-First Search (DFS)**
   - Explores as far as possible along a branch before backtracking.
   - Often finds a path, but not always the shortest one.
2. **Breadth-First Search (BFS)**
   - Explores nodes level by level, guaranteeing the shortest path in an unweighted graph.
3. **A-STAR Search**
   - Combines the benefits of DFS and BFS using a heuristic to guide the search.
4. **Hill Climbing**
   - Uses heuristics to make decisions at each step but doesn't guarantee a solution.

---

## **Adding the Demo**
1. Run the program with the parameters:
   - **Grid size**: `20x20`
   - **Percentage of nodes removed**: `40%`
   - **Algorithm**: **A* Search**

![Demo GIF](demo.gif)
