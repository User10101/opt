#include <iostream>

using namespace std;

int main()
{
  int n;
  cin >> n;
  int cum_rate = 0;
  int rate;
  int min_rate = 1000;
  for (size_t i = 0; i < n; ++i) {
    cin >> rate;
    if (rate < min_rate) {
      min_rate = rate;
    }
    cum_rate += rate;
  }

  cout << cum_rate - min_rate;
  return 0;
}
