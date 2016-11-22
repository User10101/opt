#include <iostream>

using namespace std;

int main()
{
  int p;
  cin >> p;
  bool flag = false;
  for (int i = 0; i < p; ++i) {
    flag = false;
    for (int j = 0; j < p; ++j) {
      if ((j*j - i)%p == 0) {
	cout << j << ' ';
	flag = true;
	break;
      }
    }

    if (!flag) {
      cout << -1 << ' ';
    }
  }

  return 0;
}
