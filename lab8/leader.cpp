#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  int n;
  cin >> n;
  double count = pow(2, n);
  if (count > 1.0e6) {
    cout << "TOO HARD";
    return 0;
  }
  cout << count;
  return 0;
}
