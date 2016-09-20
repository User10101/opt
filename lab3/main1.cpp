#include <iostream>
#include <fstream>
#include <vector>

#define BOG -1

using namespace std;

inline bool is_bog(int x)
{
  if (x < 0) {
    return true;
  }

  return false;
}

int tmax(int x1, int x2, int x3)
{
  if (is_bog(x1) && is_bog(x2)) {
    return x3;
  } else if (is_bog(x2) && is_bog(x3)) {
    return x1;
  } else if (is_bog(x1) && is_bog(x3)) {
    return x2;
  } else if (is_bog(x1)) {
    return max(x2, x3);
  } else if (is_bog(x2)) {
    return max(x1, x3);
  } else if (is_bog(x3)) {
    return max(x1, x2);
  } else {
    return max(max(x1, x2), x3);
  }
}

int main()
{
  ifstream ist;
  ist.open("lepus.in");
  unsigned short n;
  ist >> n;
  char c;
  std::vector<char> weights(n);
  for (size_t i = 0; i < n; ++i) {
    ist >> c;
    switch (c)
      {
      case 'w':
	weights[i] = -1;
	break;
      case '.':
	weights[i] = 0;
	break;
      case '"':
	weights[i] = 1;
	break;
      }
  }
  ist.close();

  char invalid = 0;
  int opt1, opt2, opt3;
  vector<int> sums(n);
  for (int i = 1; i < sums.size(); ++i) {
    if (weights[i] == BOG) {
      ++invalid;
      if (invalid == 5) {
	sums[n - 1] = -1;
	break;
      }
      continue;
    }
    
    opt1 = (i - 1 >= 0 && weights[i - 1] != BOG) ? sums[i - 1] : BOG;
    opt2 = (i - 3 >= 0 && weights[i - 3] != BOG) ? sums[i - 3] : BOG;
    opt3 = (i - 5 >= 0 && weights[i - 5] != BOG) ? sums[i - 5] : BOG;

    // Зайчик не может достичь клетки n.
    if (opt1 == BOG && opt2 == BOG && opt3 == BOG) {
      ++invalid;
      if (5 == invalid || i == n - 1) {
	sums[n - 1] = -1;
	break;
      }
      continue;
    }
    invalid = 0;
    sums[i] = tmax(opt1, opt2, opt3) + weights[i];
  }

  ofstream ost;
  ost.open("lepus.out");
  ost << sums[n - 1];
  ost.close();

  return 0;
}
