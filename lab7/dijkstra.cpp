#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

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
  Vertex_comp(const vector<Vertex> *v)
    : vert(v)
  {
    // DO NOTHING
  }

  bool operator()(int v1, int v2)
  {
    return (*vert)[v1].D() >= (*vert)[v2].D();
  }
private:
  const vector<Vertex> *vert;
};

ostream& operator << (ostream &ost, const Vertex &v)
{
  for (auto iter : v.neighbors) {
    cout << '[' << iter.v << ", " << iter.w << "]" << "\n";
  }

  return ost;
}

void print_graph(const vector<Vertex> &g)
{
  for (int i = 0; i < g.size(); ++i) {
    cout << i << " --- " << g[i] << "\n";
  }
}

void dijkstra(vector<Vertex> &g, int s)
{
  int max_d = 100000;
  for (size_t i = 0; i < g.size(); ++i) {
    g[i].D(max_d);
  }
  g[s].D(0);

  Vertex_comp comp(&g);
  set<int> H;
  priority_queue<int, vector<int>, Vertex_comp> Q(comp);
  for (int i = 0; i < g.size(); ++i) {
    Q.push(i);
  }
  for (int i = 0; i < g.size(); ++i) {
    int v = Q.top();
    Q.pop();
    while (H.find(v) != end(H)) {
      if (Q.size() == 0) {
	return;
      }
      v = Q.top();
      Q.pop();
    }
    H.insert(v);
    Edge e = g[v].next_edge();
    while (e != g[v].last_edge) {
      if (H.find(e.v) == end(H)) {
	g[e.v].D(g[v].D() + e.w);
	Q.push(e.v);
      }
      e = g[v].next_edge();
    }
  }
}

void dijkstra_basic(vector<Vertex> &g, int s)
{
  int max_d = 100000;
  for (size_t i = 0; i < g.size(); ++i) {
    g[i].D(max_d);
  }
  g[s].D(0);

  Vertex_comp comp(&g);
  set<int> H;
  priority_queue<int, vector<int>, Vertex_comp> Q(comp);
  for (int i = 0; i < g.size(); ++i) {
    Q.push(i);
  }
  for (int i = 0; i < g.size(); ++i) {
    int v = Q.top();
    Q.pop();
    while (H.find(v) != end(H)) {
      if (Q.size() == 0) {
	return;
      }
      v = Q.top();
      Q.pop();
    }
    H.insert(v);
    Edge e = g[v].next_edge();
    while (e != g[v].last_edge) {
      if (H.find(e.v) == end(H)) {
	g[e.v].D(g[v].D() + e.w);
	Q.push(e.v);
      }
      e = g[v].next_edge();
    }
  }
}

int main()
{
  int s, N, M;
  ifstream ist;
  ist.open("dijkstra.in");
  ist >> s;
  ist >> N >> M;
  vector<Vertex> G(N);
  int u, v, w;
  for (size_t i = 0; i < G.size(); ++i) {
    ist >> u >> v >> w;
    cout << u << ' ' << v << ' ' << w << endl;
    G[u].add_edge(u, v, w);
    G[v].add_edge(v, u, w);
  }
  ist.close();
  print_graph(G);
  dijkstra(G, s);

  ofstream ost("dijkstra.out");
  for (size_t i = 0; i < G.size(); ++i) {
    ost << G[i].D() << "\n";
  }
  ost.close();

  return 0;
}
