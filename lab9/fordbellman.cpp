#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#define MAX_D 100000
#define NO_PATH -100000

using namespace std;

class Edge
{
public:
  Edge(int _u, int _v, int _w)
    : u(_u), v(_v), w(_w) {}

  bool operator < (const Edge &e)
  {
    return w < e.w;
  }

  int u;
  int v;
  int w;
};

std::vector<int> Ford_Bellman(std::vector<Edge> &e, int N, int s)
{
  int **dist = new int*[N];
  for (size_t i = 0; i < N; ++i) {
    dist[i] = new int[N - 1];
  }
  for (size_t i = 0; i < N; ++i) {
    dist[0][i] = MAX_D;
  }
  dist[0][s] = 0;
  for (int i = 1; i < N - 1; ++i) {
    for (int j = 0; j < e.size(); ++j) {
      if (dist[i - 1][e[j].u] + e[j].w < dist[i - 1][e[j].v]) {
	dist[i][e[j].v] = dist[i - 1][e[j].u] + e[j].w;
      }
    }
  }

  std::vector<int> res(N);
  for (size_t i = 0; i < N; ++i) {
    res[i] = dist[N - 2][i];
  }

  return res;
}

int main()
{
  int s, N, M;
  ifstream ist;
  ist.open("ford_bellman.in");
  ist >> s;
  ist >> N >> M;
  std::vector<Edge> e;
  int u, v, w;
  for (size_t i = 0; i < M; ++i) {
    ist >> u >> v >> w;
    e.push_back(Edge(u, v, w));
  }
  ist.close();
  std::vector<int> res = Ford_Bellman(e, N, s);

  ofstream ost("ford_bellman.out");
  for (size_t i = 0; i < res.size(); ++i) {
    ost << res[i] << "\n";
  }
  ost.close();

  return 0;
}
