#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> numbers(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> numbers[i];
  }

  int prev_ndiv;
  int ndiv = 0;
  int div = 1;
  while (true) {
    prev_ndiv = ndiv;
    ndiv = 0;
    for (size_t i = 0; i < n; ++i) {
      if (numbers[i] % div == 0) {
	ndiv++;
      }
    }
    if (ndiv == 0) {
      break;
    }
    div <<= 1;
  }

  cout << div/2  << ' ' << prev_ndiv;
}
