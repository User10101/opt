#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
  double a, b, c;
  cin >> a >> b >> c;
  long double iy = -c/b;
  double ix = -c/a;
  cout << setprecision(11) << (abs(ix) * abs(iy))/2.;
  return 0;
}
