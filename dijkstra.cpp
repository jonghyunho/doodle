#include <iostream>
#include <limits>

#define V 9

int minDistance(int dist[V], bool visit[V]) {
  int min = INT_MAX;
  int min_index = -1;

  for (int i = 0; i < V; i++) {
    if (min > dist[i] && visit[i] == false) {
      min = dist[i];
      min_index = i;
    }
  }

  return min_index;
}

void printParent(int parent[V], int v) {
  if (parent[v] == -1) {
    return;
  }

  printParent(parent, parent[v]);

  std::cout << v << " ";
}

void printSolution(int dist[V], int parent[V], int start) {
  for (int i = 0; i < V; i++) {
    if (start == i) continue;

    std::cout << start << " -> " << i << " : " << dist[i] << std::endl;
    printParent(parent, i);
    std::cout << std::endl << std::endl;
  }
}

void dijkstra(int graph[V][V], int start) {
  int dist[V];
  int parent[V];
  bool visit[V];

  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    parent[i] = -1;
    visit[i] = false;
  }

  dist[start] = 0;

  for (int cnt = 0; cnt < V - 1; cnt++) {
    int u = minDistance(dist, visit);
    visit[u] = true;

    for (int v = 0; v < V; v++) {
      if (!visit[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        parent[v] = u;
      }
    }
  }

  printSolution(dist, parent, start);
}

int main() {
  int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                     {4, 0, 8, 0, 0, 0, 0, 11, 0},
                     {0, 8, 0, 7, 0, 4, 0, 0, 2},
                     {0, 0, 7, 0, 9, 14, 0, 0, 0},
                     {0, 0, 0, 9, 0, 10, 0, 0, 0},
                     {0, 0, 4, 0, 10, 0, 2, 0, 0},
                     {0, 0, 0, 14, 0, 2, 0, 1, 6},
                     {8, 11, 0, 0, 0, 0, 1, 0, 7},
                     {0, 0, 2, 0, 0, 0, 6, 7, 0}};

  dijkstra(graph, 0);
  return 0;
}
