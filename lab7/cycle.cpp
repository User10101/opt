#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

enum Colors {White, Gray, Black};

class Vertex
{
public:
  Vertex();
  ~Vertex();

  void add_edge(int v);
  int next_edge();

  Colors color() const;
  void color(Colors);

  static const int last_edge = -1;
  static const int empty_edge = -2;
private:
  Colors col;
  list<int> neighbors;
  list<int>::iterator curr_edge;
  bool is_clear;

  friend ostream& operator << (ostream &ost, const Vertex &v);
};

Vertex::Vertex()
  : col(White), curr_edge(nullptr), is_clear(true)
{
  // DO NOTHING
}

Vertex::~Vertex()
{
  // DO NOTHING
}

void Vertex::add_edge(int v)
{
  neighbors.push_back(v);
}

int Vertex::next_edge()
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

Colors Vertex::color() const
{
  return col;
}

void Vertex::color(Colors c)
{
  col = c;
}

ostream& operator << (ostream &ost, const Vertex &v)
{
  for (auto iter : v.neighbors) {
    cout << iter << ' ';
  }

  return ost;
}

void print_graph(const vector<Vertex> &g)
{
  for (auto v : g) {
    cout << v << "\n";
  }
}

int main()
{
  int N, M;
  ifstream ist;
  ist.open("cycle.in");
  ist >> N >> M;

  vector<Vertex> G(N);
  stack<int> last_vertex;
  vector<int> path;

  int i, j;
  for (size_t k = 0; k < M; ++k) {
    ist >> i >> j;
    G[i-1].add_edge(j - 1);
  }
  ist.close();
  print_graph(G);

  ofstream ost;
  ost.open("cycle.out");
  for (size_t i = 0; i < N; ++i) {
    if (G[i].color() == White) {
      int next_v;
      last_vertex.push(i);
      path.push_back(i);
      G[i].color(Gray);
      while (!last_vertex.empty()) {
	next_v = G[last_vertex.top()].next_edge();
	if (G[last_vertex.top()].last_edge == next_v) {
	  G[last_vertex.top()].color(Black);
	  last_vertex.pop();
	} else {
	  G[last_vertex.top()].color(Gray);
	  if (G[next_v].color() == Gray) {
	    ost << "YES\n";
	    stack<int> loop_path;
	    int v;
	    while(1) {
	      v = last_vertex.top();
	      loop_path.push(v);
	      if (v == next_v) {
		break;
	      }
	      last_vertex.pop();
	    }
	    while (!loop_path.empty()) {
	      ost << loop_path.top() + 1 << ' ';
	      loop_path.pop();
	    }
	    ost.close();
	    return 0;
	  }

	  last_vertex.push(next_v);
	  path.push_back(next_v);
	}
      }
    }
  }

  ost << "NO\n";
  ost.close();
}
