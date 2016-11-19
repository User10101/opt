#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int policeman(const vector<size_t> &street_begin, const vector<size_t> &street_end,
	       size_t min, size_t n)
{
  if (n == min) {
    return 0;
  }

  for (size_t i = 0; i < street_begin.size(); ++i) {
    if ((street_begin[i] == (n+1) && street_end[i] == (min+1)) ||
	(street_begin[i] == (min+1) && street_end[i] == (n+1))) {
      return 0;
    }
  }
  return 1;
}

int main()
{
  size_t n, m;
  cin >> n >> m;
  vector<size_t> street_begin(m);
  vector<size_t> street_end(m);
  vector<size_t> squares(n);
  for (size_t i = 0; i < m; ++i) {
    cin >> street_begin[i] >> street_end[i];
    squares[street_begin[i] - 1]++;
    squares[street_end[i] - 1]++;
  }

  size_t min = 0;
  for (size_t i = 0; i < n; ++i) {
    if (squares[i] < squares[min]) {
      min = i;
    }
  }

  int degree = 0;
  for (size_t i = 0; i < n; ++i) {
    if (degree != squares[min]) {
      int res = policeman(street_begin, street_end, min, i);
      cout << res << ' ';
      if (res == 0) {
	++degree;
      }
    } else {
      cout << 1 << ' ';
    }
  }

  return 0;
}
