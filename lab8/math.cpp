#include <iostream>

using namespace std;

int main()
{
  size_t p;
  cin >> p;
  bool flag = false;
  for (size_t i = 0; i < p; ++i) {
    flag = false;
    for (size_t j = 0; j < p; ++j) {
      if ((j*j)%p == i) {
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
