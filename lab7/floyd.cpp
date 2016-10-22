#include <fstream>
#include <cmath>

using namespace std;

int main()
{
  int N;
  ifstream ist;
  ist.open("floyd.in");
  ist >> N;
  
  int W[N][N];
  for (unsigned int i = 0; i < N; ++i) {
    for (unsigned int j = 0; j < N; ++j) {
      ist >> W[i][j];
    }
  }
  ist.close();

  for (unsigned int k = 0; k < N; ++k) {
    for (unsigned int i = 0; i < N; ++i) {
      for (unsigned int j = 0; j < N; ++j) {
	W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
      }
    }
  }

  ofstream ost;
  ost.open("floyd.out");
  for (unsigned int i = 0; i < N; ++i) {
    for (unsigned int j = 0; j < N; ++j) {
      ost << W[i][j] << ' ';
    }
    ost << endl;
  }
  ost.close();

  return 0;
}
