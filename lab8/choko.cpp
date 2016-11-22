#include <iostream>

using namespace std;

int main()
{
  int N, k;
  cin >> N >> k;

  for (int i = 1; i <= N; ++i) {
    if ((N % i) != 0) {
      continue;
    }
    for (int j = 1; j <= N; ++j) {
      if ((N % j) != 0) {
	continue;
      }
      if ((N*N / (i*j)) == k) {
	cout << "YES";
	return 0;
      }
    }
  }

  cout << "NO";
  return 0;
}
