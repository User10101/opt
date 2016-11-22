#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  size_t n, m;
  cin >> n >> m;
  vector<size_t> street_begin(m);
  vector<size_t> street_end(m);
  vector<size_t> squares(n);
  for (size_t i = 0; i < m; ++i) {
    cin >> street_begin[i] >> street_end[i];
    street_begin[i]--;
    street_end[i]--;
    squares[street_begin[i]]++;
    squares[street_end[i]]++;
  }

  size_t min = 0;
  for (size_t i = 0; i < n; ++i) {
    if (squares[i] < squares[min]) {
      min = i;
    }
  }

  vector<int> policemans(n);
  fill(policemans.begin(), policemans.end(), 1);
  policemans[min] = 0;
  for (size_t i = 0; i < m; ++i) {
    if (street_begin[i] == min) {
      policemans[street_end[i]] = 0;
    }
    if (street_end[i] == min) {
      policemans[street_begin[i]] = 0;
    }
  }
  for (size_t i = 0; i < n; ++i) {
    cout << policemans[i] << ' ';
  }
  cout << endl;

  return 0;
}
