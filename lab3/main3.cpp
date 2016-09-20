#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  int N, M;
  ifstream ist;
  ist.open("knight.in");
  ist >> N >> M;
  ist.close();

  unsigned int field[N][M];
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      field[i][j] = 0;
    }
  }

  int opt1, opt2;
  for (short i = 0; i < N; ++i) {
    for (short j = 0; j < M; ++j) {
      if (i == 0 && j == 0) {
	field[i][j] =1;
	continue;
      }
      if (i - 2 >= 0 && j - 1 >= 0) {
	opt1 = field[i - 2][j - 1];
      } else {
	opt1 = 0;
      }

      if (i - 1 >= 0 && j - 2 >= 0) {
	opt2 = field[i - 1][j - 2];
      } else {
	opt2 = 0;
      }

      field[i][j] = opt1 + opt2;
    }
  }

  ofstream ost;
  ost.open("knight.out");
  ost << field[N - 1][M - 1];
  ost.close();

  return 0;
}
