#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>

#define MAX_D 100000

using namespace std;

class Vertex;

class Edge
{
public:
  Edge(int _u, int _v, int _w);
  virtual ~Edge();

  bool operator != (const Edge &rhs);

  int u;
  int v;
  int w;
};

Edge::Edge(int _u, int _v, int _w)
  : u(_u), v(_v), w(_w)
{
  // DO NOTHING
}

Edge::~Edge()
{
  // DO NOTHING
}

bool Edge::operator != (const Edge &rhs)
{
  return !((u == rhs.u) && (v == rhs.v) && (w == rhs.w));
}

class Vertex
{
public:
  Vertex();
  ~Vertex();

  void add_edge(int u, int v, int w);
  Edge next_edge();

  //  int weight(int v);

  int D() const;
  void D(int d);

  int prev_v() const;
  void prev_v(int v);

  const Edge last_edge;
private:
  int d;
  int pv;

  list<Edge> neighbors;
  list<Edge>::iterator curr_edge;
  bool is_clear;

  friend ostream& operator << (ostream &ost, const Vertex &v);
};

Vertex::Vertex()
  : is_clear(true), last_edge(-1, -1, -1), pv(-1)
{
  // DO NOTHING
}

Vertex::~Vertex()
{
  // DO NOTHING
}

void Vertex::add_edge(int u, int v, int w)
{
  neighbors.push_back(Edge(u, v, w));
}

Edge Vertex::next_edge()
{
  if (is_clear) {
    curr_edge = begin(neighbors);
    is_clear = false;
  }

  if (curr_edge == end(neighbors)) {
    return last_edge;
  } else {
    return *(curr_edge++);
  }
}

int Vertex::D() const
{
  return d;
}

void Vertex::D(int _d)
{
  d = _d;
}

int Vertex::prev_v() const
{
  return pv;
}

void Vertex::prev_v(int v)
{
  pv = v;
}

class Vertex_comp
{
public:
  Vertex_comp()
  {
    // DO NOTHING
  }

  bool operator()(pair<int, int> &lhs, pair<int, int> &rhs)
  {
    return lhs.second >= rhs.second;
  }
};

ostream& operator << (ostream &ost, const Vertex &v)
{
  for (auto iter : v.neighbors) {
    cout << '[' << iter.v << ", " << iter.w << "]" << "\n";
  }

  return ost;
}

void print_graph(Vertex *g, int N)
{
  for (int i = 0; i < N; ++i) {
    cout << i << " --- " << g[i] << "\n";
  }
}

void dijkstra(Vertex *g, int N, int s)
{
  for (size_t i = 0; i < N; ++i) {
    g[i].D(MAX_D);
  }
  g[s].D(0);

  set<int> H;
  priority_queue<pair<int, int>, vector<pair<int,int>>, Vertex_comp> Q;
  for (int i = 0; i < N; ++i) {
    Q.emplace(i, g[i].D());
  }
  for (int i = 0; i < N; ++i) {
    int v = (Q.top()).first;
    Q.pop();
    while (H.find(v) != end(H)) {
      if (Q.size() == 0) {
	return;
      }
      v = Q.top().first;
      Q.pop();
    }
    H.insert(v);
    Edge e = g[v].next_edge();
    while (e != g[v].last_edge) {
      if (H.find(e.v) == end(H) && g[e.v].D() > g[v].D() + e.w) {
	g[e.v].D(g[v].D() + e.w);
	g[e.v].prev_v(v);
	Q.emplace(e.v, g[e.v].D());
      }
      e = g[v].next_edge();
    }
  }
}

int main()
{
  int n;
  ifstream ist;
  ist.open("rootdist.in");
  ist >> n;
  Vertex *G = new Vertex[n];
  int parent;
  for (size_t i = 1; i < n; ++i) {
    ist >> parent;
    G[i].add_edge(i, parent-1, 1);
    G[parent-1].add_edge(parent-1, i, 1);
  }
  ist.close();
  dijkstra(G, n, 0);
  list<int> mdv;
  int max_d = 0;
  for (size_t i = 0; i < n; ++i) {
    if (G[i].D() > max_d) {
      max_d = G[i].D();
      mdv.clear();
      mdv.push_back(i+1);
    } else if (G[i].D() == max_d) {
      mdv.push_back(i+1);
    }
  }

  ofstream ost;
  ost.open("rootdist.out");
  ost << max_d << "\n" << mdv.size() << "\n";
  for (auto iter : mdv) {
    ost << iter << ' ';
  }
  ost.close();

  delete[] G;
  return 0;
}
