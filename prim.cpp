#include <iostream>
#include <limits>

#define V 5

int minKey(int key[V], bool visit[V]) {
  int min = INT_MAX;
  int min_index = -1;

  for (int v = 0; v < V; v++) {
    if (key[v] < min && !visit[v]) {
      min = key[v];
      min_index = v;
    }
  }

  return min_index;
}

void printMST(int graph[V][V], int parent[V]) {
  for (int i = 1; i < V; i++) {
    std::cout << parent[i] << " -> " << i << " : " << graph[parent[i]][i]
              << std::endl;
  }
}

void primMST(int graph[V][V]) {
  int parent[V];
  int key[V];
  bool visit[V];

  for (int v = 0; v < V; v++) {
    parent[v] = -1;
    key[v] = INT_MAX;
    visit[v] = false;
  }

  key[0] = 0;

  for (int cnt = 0; cnt < V - 1; cnt++) {
    int u = minKey(key, visit);
    visit[u] = true;

    for (int v = 0; v < V; v++) {
      if (!visit[v] && graph[u][v] && graph[u][v] < key[v]) {
        key[v] = graph[u][v];
        parent[v] = u;
      }
    }
  }

  printMST(graph, parent);
}

int main() {
  int graph[V][V] = {{0, 2, 0, 6, 0},
                     {2, 0, 3, 8, 5},
                     {0, 3, 0, 0, 7},
                     {6, 8, 0, 0, 9},
                     {0, 5, 7, 9, 0}};

  primMST(graph);

  return 0;
}
