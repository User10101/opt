#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int n, d;
  cin >> n >> d;
  vector<int> x(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> x[i];
  }

  int a, b;
  int count = 0;
  for (size_t i = 0; i < x.size(); ) {
    ++count;
    a = x[i];
    b = a + d;
    while (a <= x[i] && x[i] <= b) ++i;
  }

  cout << count;
  return 0;
}
