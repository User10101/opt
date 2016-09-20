#include <iostream>
#include <fstream>

#define FORBIDDEN -1

using namespace std;

int tmin(int x1, int x2, int x3)
{
  if (x1 == FORBIDDEN && x2 == FORBIDDEN) {
    return x3;
  } else if (x2 == FORBIDDEN && x3 == FORBIDDEN) {
    return x1;
  } else if (x1 == FORBIDDEN && x3 == FORBIDDEN) {
    return x2;
  } else if (x1 == FORBIDDEN) {
    return min(x2, x3);
  } else if (x2 == FORBIDDEN) {
    return min(x1, x3);
  } else if (x3 == FORBIDDEN) {
    return min(x1, x2);
  } else {
    return min(min(x1, x2), x3);
  }
}

int main()
{
  unsigned short field[8][8];
  unsigned int costs[8][8];
  ifstream ist;
  ist.open("king2.in");
  for (size_t i = 0; i < 8; ++i) {
    for (size_t j = 0; j < 8; ++j) {
      ist >> field[i][j];
    }
  }
  ist.close();

  int opt1, opt2, opt3;
  for (int i = 7; i >= 0; --i) {
    for (int j = 0; j < 8; ++j) {
      if (i == 7 && j == 0) {
	costs[i][j] = 0;
	continue;
      }

      opt1 = (i + 1 < 8) ? costs[i + 1][j] : FORBIDDEN;
      opt2 = (j - 1 >= 0) ? costs[i][j - 1] : FORBIDDEN;
      opt3 = (j - 1 >= 0 && i + 1 < 8) ? costs[i + 1][j - 1] : FORBIDDEN;
      costs[i][j] = tmin(opt1, opt2, opt3) + field[i][j];
    }
  }

  ofstream ost;
  ost.open("king2.out");
  ost << costs[0][7];
  ost.close();
  
  return 0;
}
