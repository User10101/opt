#include <fstream>
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <queue>
#include <set>
//#include <algorithm>

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

  void add_edge(int u, int v, int w = 1);
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
  Vertex_comp(Vertex *v)
    : vert(v)
  {
    // DO NOTHING
  }

  bool operator()(int v1, int v2)
  {
    return vert[v1].D() >= vert[v2].D();
  }
private:
  const Vertex *vert;
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
	  g[p].prev_v(v);
	  return level + 1;
	}
	if (H.find(e.v) == end(H)) {
	  g[e.v].D(level+1);
	  g[e.v].prev_v(v);
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
  int x1, y1, x2, y2;
  ifstream ist;
  ist.open("knight1.in");
  char fl[4];
  char sl[4];
  ist.getline(fl, 4);
  ist.getline(sl, 4);
  x1 = fl[0] - 'a';
  y1 = fl[1] - '0' - 1;
  x2 = sl[0] - 'a';
  y2 = sl[1] - '0' - 1;
  ist.close();
  Vertex *G = new Vertex[64];
  int ar[64][64];
  for (size_t i = 0; i < 64; ++i) {
    for (size_t j = 0; j < 64; ++j) {
      ar[i][j] = 0;
    }
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (i - 2 >= 0 && j - 1 >= 0) {
	G[i*8+j].add_edge(i*8+j, (i-2)*8 + (j-1));
      }
      if (i - 2 >= 0 && j + 1 < 8) {
	G[i*8+j].add_edge(i*8+j, (i-2)*8 + (j+1));
      }
      if (i - 1 >= 0 && j - 2 >= 0) {
	G[i*8+j].add_edge(i*8+j, (i-1)*8 + (j-2));
      }
      if (i - 1 >= 0 && j + 2 < 8) {
	G[i*8+j].add_edge(i*8+j, (i-1)*8 + (j+2));
      }
      if (i + 2 < 8 && j - 1 >= 0) {
	G[i*8+j].add_edge(i*8+j, (i+2)*8 + (j-1));
      }
      if (i + 2 < 8 && j + 1 < 8) {
	G[i*8+j].add_edge(i*8+j, (i+2)*8 + (j+1));
      }
      if (i + 1 < 8 && j - 2 >= 0) {
	G[i*8+j].add_edge(i*8+j, (i+1)*8 + (j-2));
      }
      if (i + 1 < 8 && j + 2 < 8) {
	G[i*8+j].add_edge(i*8+j, (i+1)*8 + (j+2));
      }
    }
  }
  ofstream ost;
  ost.open("knight1.out");
  bfs(G, 64, x1*8+y1, x2*8+y2);
  stack<pair<char, int>> path;
  int i = x2*8 + y2;
  while(true) {
    path.push(pair<char, int>(i/8 + 'a', i%8 + 1));
    i = G[i].prev_v();
    if (i == (x1*8 + y1)) {
      path.push(pair<char, int>(i/8 + 'a', i%8 + 1));
      break;
    }
  }
  while (path.size()) {
    pair<char, int> p = path.top();
    path.pop();
    ost << p.first << p.second << endl;
  }
  ost.close();

  delete[] G;
  return 0;
}
