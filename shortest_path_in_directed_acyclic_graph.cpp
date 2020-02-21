#include <iostream>
#include <list>
#include <stack>

struct AdjacentNode {
  int v = 0;
  int weight = 0;

  AdjacentNode(int _v, int _weight) : v(_v), weight(_weight) {}
};

class Graph {
 public:
  Graph(int size) : size_(size) { adj_ = new std::list<AdjacentNode>[size]; }

  virtual ~Graph() { delete[] adj_; }

  void addEdge(int u, int v, int weight) {
    AdjacentNode node(v, weight);
    adj_[u].push_back(node);
  }

  void topologicalSort(int v, bool visit[], std::stack<int>& s) {
    visit[v] = true;

    std::list<AdjacentNode>::iterator it = adj_[v].begin();
    while (it != adj_[v].end()) {
      if (!visit[it->v]) topologicalSort(it->v, visit, s);

      it++;
    }

    s.push(v);
  }

  void shortestPath(int start) {
    bool* visit = new bool[size_];
    for (int i = 0; i < size_; i++) visit[i] = false;
    std::stack<int> s;

    for (int u = 0; u < size_; u++) {
      if (!visit[u]) topologicalSort(u, visit, s);
    }

    int* dist = new int[size_];
    for (int i = 0; i < size_; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    while (!s.empty()) {
      int u = s.top();
      s.pop();

      std::list<AdjacentNode>::iterator it = adj_[u].begin();
      if (dist[u] != INT_MAX) {
        while (it != adj_[u].end()) {
          AdjacentNode adj = *it;

          if (dist[adj.v] > dist[u] + adj.weight)
            dist[adj.v] = dist[u] + adj.weight;

          it++;
        }
      }
    }

    for (int i = 0; i < size_; i++) {
      if (dist[i] == INT_MAX)
        std::cout << "INF" << std::endl;
      else
        std::cout << dist[i] << std::endl;
    }

    delete[] dist;
    delete[] visit;
  }

 private:
  std::list<AdjacentNode>* adj_;
  int size_;
};

int main() {
  Graph g(6);
  g.addEdge(0, 1, 5);
  g.addEdge(0, 2, 3);
  g.addEdge(1, 3, 6);
  g.addEdge(1, 2, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 3, 7);
  g.addEdge(3, 4, -1);
  g.addEdge(4, 5, -2);

  int s = 1;
  std::cout << "Following are shortest distances from source " << s
            << std::endl;
  g.shortestPath(s);

  return 0;
}
