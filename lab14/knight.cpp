#include <fstream>
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <queue>
#include <set>

#define MAX_D 100000

using namespace std;

class Vertex;

class Edge
{
public:
  Edge(long long _u, long long _v, long long _w);
  virtual ~Edge();

  bool operator != (const Edge &rhs);

  long long u;
  long long v;
  long long w;
};

Edge::Edge(long long _u, long long _v, long long _w)
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

  void add_edge(long long u, long long v, long long w = 1);
  Edge next_edge();

  //  long long weight(long long v);

  long long D() const;
  void D(long long d);

  long long prev_v() const;
  void prev_v(long long v);

  const Edge last_edge;
private:
  long long d;
  long long pv;

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

void Vertex::add_edge(long long u, long long v, long long w)
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

long long Vertex::D() const
{
  return d;
}

void Vertex::D(long long _d)
{
  d = _d;
}

long long Vertex::prev_v() const
{
  return pv;
}

void Vertex::prev_v(long long v)
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

  bool operator()(long long v1, long long v2)
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

void print_graph(Vertex *g, long long N)
{
  for (long long i = 0; i < N; ++i) {
    cout << i << " --- " << g[i] << "\n";
  }
}

long long bfs(Vertex *g, long long N, long long s, long long p)
{
  long long level = 0;
  g[s].D(level);
  Vertex_comp comp(g);
  priority_queue<long long, vector<long long>, Vertex_comp> Q(comp);
  Q.push(s);
  set<long long> H;
  while (Q.size()) {
    long long v = Q.top();
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
  long long x1 = -1, y1, x2, y2;
  ifstream ist;
  ist.open("input.txt");
  long long N;
  ist >> N;
  Vertex *G = new Vertex[N * N];
  char ch;
  bool **forbidden = new bool*[N];
  for (size_t i = 0; i < N; ++i) {
    forbidden[i] = new bool[N];
  }

  for (long long i = 0; i < N; ++i) {
    for (long long j = 0; j < N; ++j) {
      ist >> ch;
      if (ch == '+') {
	forbidden[i][j] = true;
	continue;
      } else {
	forbidden[i][j] = false;
      }

      if (ch == '*') {
	if (x1 == -1) {
	  x1 = i;
	  y1 = j;
	} else {
	  x2 = i;
	  y2 = j;
	}
      }

      if (i - 2 >= 0 && j - 1 >= 0 && !forbidden[i - 2][j - 1]) {
	G[i*N+j].add_edge(i*N+j, (i-2)*N + (j-1));
      }
      if (i - 2 >= 0 && j + 1 < N && !forbidden[i - 2][j + 1]) {
	G[i*N+j].add_edge(i*N+j, (i-2)*N + (j+1));
      }
      if (i - 1 >= 0 && j - 2 >= 0 && !forbidden[i - 1][j - 2]) {
	G[i*N+j].add_edge(i*N+j, (i-1)*N + (j-2));
      }
      if (i - 1 >= 0 && j + 2 < N && !forbidden[i - 1][j + 2]) {
	G[i*N+j].add_edge(i*N+j, (i-1)*N + (j+2));
      }
      if (i + 2 < N && j - 1 >= 0 && !forbidden[i + 2][j - 1]) {
	G[i*N+j].add_edge(i*N+j, (i+2)*N + (j-1));
      }
      if (i + 2 < N && j + 1 < N && !forbidden[i + 2][j + 1]) {
	G[i*N+j].add_edge(i*N+j, (i+2)*N + (j+1));
      }
      if (i + 1 < N && j - 2 >= 0 && !forbidden[i + 1][j - 2]) {
	G[i*N+j].add_edge(i*N+j, (i+1)*N + (j-2));
      }
      if (i + 1 < N && j + 2 < N && !forbidden[i + 1][j + 2]) {
	G[i*N+j].add_edge(i*N+j, (i+1)*N + (j+2));
      }
    }
  }
  // for (size_t i = 0; i < N * N; ++i) {
  //   cout << i << ' ' << G[i];
  // }

  ofstream ost;
  ost.open("output.txt");
  size_t length = bfs(G, N * N, x1*N+y1, x2*N+y2);
  if (length == 0) {
    ost << length;
  } else {
    stack<pair<long long, long long>> path;
    long long i = x2*N + y2;
    while(true) {
      path.push(pair<long long, long long>(i/N, i%N));
      i = G[i].prev_v();
      if (i == (x1*N + y1)) {
	path.push(pair<long long, long long>(i/N, i%N));
	break;
      }
    }
    ost << length + 1 << "\n";
    while (path.size()) {
      pair<long long, long long> p = path.top();
      path.pop();
      ost << p.first << ' ' << p.second << endl;
    }
  }
  ost.close();

  delete[] G;
  return 0;
}
