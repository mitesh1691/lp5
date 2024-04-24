#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Graph class representing the adjacency list
class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    // Add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    // Parallel Breadth-First Search
    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;
        double startTime = omp_get_wtime();

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); i++) {
                int n = adj[v][i];
                if (!visited[n]) {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }

        double endTime = omp_get_wtime();
        cout << "\nExecution Time (BFS): " << endTime - startTime << " seconds" << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Create a graph
    Graph g(V);

    cout << "Enter edges (vertex pairs):\n";
    for (int i = 0; i < E; ++i) {
        int v, w;
        cin >> v >> w;
        if (v < 0 || v >= V || w < 0 || w >= V) {
            cout << "Invalid vertex index!" << endl;
            return 1; // Exit with error code
        }
        g.addEdge(v, w);
    }

    int startVertex;
    cout << "Enter the start vertex for BFS: ";
    cin >> startVertex;

    cout << "Breadth-First Search (BFS): ";
    g.parallelBFS(startVertex);
    cout << endl;

    return 0;
}

// how to run: 
// open terminal: 
// enter this:
            // g++ -o bfs bfs.cpp -fopenmp
// then this: 
            // ./bfs


// Draw this Graph: 
//          - 1 ------------- 3
//        -   |               |
//      -     |               | 
//    -       |               | 
//  0         |               | 
//    -       |               | 
//      -     |               |   
//        -   |               |
//          - 2 --------------4



// Sample Output: 
// Enter the number of vertices: 5
// Enter the number of edges: 6
// Enter edges (vertex pairs):
// 0 1
// 0 2
// 1 3
// 1 2
// 2 4
// 3 4
// Enter the start vertex for BFS: 0
// Breadth-First Search (BFS): 0 1 2 3 4
// Execution Time (BFS): 0.00165355 seconds



// don't worry if your output is different, it is correct (run multiple times if you want the same output)


