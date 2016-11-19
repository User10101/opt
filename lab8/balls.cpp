#include <iostream>

using namespace std;

int main()
{
  size_t n;
  cin >> n;
  size_t max = 0, num;
  for (size_t i = 0; i < n; ++i) {
    cin >> num;
    if (num > max) {
      max = num;
    }
  }
  cout << max;
  return 0;
}
