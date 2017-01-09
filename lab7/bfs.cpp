#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
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

  const Edge last_edge;
private:
  int d;
  int no;

  list<Edge> neighbors;
  list<Edge>::iterator curr_edge;
  bool is_clear;

  friend ostream& operator << (ostream &ost, const Vertex &v);
};

Vertex::Vertex()
  : is_clear(true), last_edge(-1, -1, -1)
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
	Q.emplace(e.v, g[e.v].D());
      }
      e = g[v].next_edge();
    }
  }
}

int bfs(Vertex *g, int N, int s, int p)
{
  int level = 0;
  g[s].D(level);
  Vertex_comp comp(g);
  priority_queue<int, vector<int>, Vertex_comp> Q(comp);
  Q.push(s);
  set<int> H;
  while (Q.size()) {
    int v = Q.top();
    Q.pop();
    if (g[v].D() > level) {
      ++level;
    }
    if (H.find(v) == H.end()) {
      H.insert(v);
      Edge e = g[v].next_edge();
      while (e != g[v].last_edge) {
	if (e.v == p) {
	  return level + 1;
	}
	if (H.find(e.v) == end(H)) {
	  g[e.v].D(level+1);
	  Q.push(e.v);
	}
	e = g[v].next_edge();
      }
    }
  }

  return 0;
}

int main()
{
  int N, S, F;
  ifstream ist;
  ist.open("bfs.in");
  ist >> N >> S >> F;
  Vertex *G = new Vertex[N];
  int is_edge;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      ist >> is_edge;
      if (is_edge) {
	G[i].add_edge(i, j, 1);
      }
    }
  }
  ist.close();
  ofstream ost;
  ost.open("bfs.out");
  dijkstra(G, N, S-1);
  if (G[F-1].D() == MAX_D) {
    ost << 0;
  } else {
    ost << G[F-1].D();
  }
  ost.close();

  delete[] G;
  return 0;
}
