#include <iostream>
#include <vector>
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
    

    // Parallel Depth-First Search
    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        double startTime = omp_get_wtime();
        parallelDFSUtil(startVertex, visited);
        double endTime = omp_get_wtime();
        cout << "\nExecution Time (DFS): " << endTime - startTime << " seconds" << endl;
    }

    // Parallel DFS utility function
    void parallelDFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++) {
            int n = adj[v][i];
            if (!visited[n])
                parallelDFSUtil(n, visited);
        }
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
    cout << "Enter the start vertex for DFS: ";
    cin >> startVertex;

    cout << "Depth-First Search (DFS): ";
    g.parallelDFS(startVertex);
    cout << endl;

    return 0;
}


// how to run: 
// open terminal: 
// enter this:
            // g++ -o dfs dfs.cpp -fopenmp
// then this: 
            // ./dfs


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

// sample output: 
// Enter the number of vertices: 5
// Enter the number of edges: 6
// Enter edges (vertex pairs):
// 0 1
// 0 2
// 1 3
// 1 2
// 2 4
// 3 4
// Enter the start vertex for DFS: 0
// Depth-First Search (DFS): 0 1 3 4 2
// Execution Time (DFS): 0.00828835 seconds

// don't worry if your output is different, it is correct (run multiple times if you want the same output)
