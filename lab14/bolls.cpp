#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  int N, M;
  ifstream ist("input.txt");
  ist >> N >> M;
  ist.close();

  ofstream ost("output.txt");
  ost << N / M;
  ost.close();

  return 0;
}
