#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    const int INF = numeric_limits<int>::max();
    vector<int> dist(V, INF);
    dist[source] = 0;

    // Bellman-Ford
    for (int i = 1; i < V; ++i) {
        for (const auto &edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }

    // Check for negative cycle
    for (const auto &edge : edges) {
        if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
            cout << "Graph contains a negative-weight cycle.\n";
            return 0;
        }
    }

    // Output in single line
    cout << "  vertex distance from source " << source << "  ";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF)
            cout << "INF ";
        else
            cout << dist[i] << " ";
    }

    return 0;
}
