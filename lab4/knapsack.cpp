#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int S;
  short N;
  cin >> S >> N;

  vector<int> weights(N);
  for (size_t i = 0; i < N; ++i) {
    cin >> weights[i];
  }

  vector<bool> possible_weights(S+1);
  possible_weights[0] = true;
  for (size_t i = 1; i <= S; ++i) {
    possible_weights[i] = false;
  }

  vector<bool> prev_possible_weights = possible_weights;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j <= S; ++j) {
      if (j - weights[i] >= 0 && prev_possible_weights[j - weights[i]]) {
	possible_weights[j] = true;
      }
    }

    prev_possible_weights = possible_weights;
  }

  int max = 0;
  for (int i = S; i >= 0; --i) {
    if (possible_weights[i]) {
      max = i;
      break;
    }
  }

  cout << max;
  
  return 0;
}
