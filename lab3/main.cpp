#include <iostream>
#include <vector>
#include <fstream>

int dyn_ladder(const std::vector<int> &costs)
{
  //std::vector<int> path;
  std::vector<int> sums(costs.size() + 1);
  sums[0] = 0;
  sums[1] = costs[0];
  for (int i = 2; i < sums.size(); ++i) {
    if (sums[i - 1] > sums[i - 2]) {
      sums[i] = sums[i - 1] + costs[i - 1];
      //path.push_back(i - 1);
    } else {
      sums[i] = sums[i - 2] + costs[i - 1];
      //path.push_back(i - 2);
    }
  }
  
  //return std::pair<int, std::vector<int>>(sums[sums.size() - 1], path);
  return sums[sums.size() - 1];
}

int main()
{
  std::ifstream ist;
  ist.open("ladder.in");
  int n;
  ist >> n;
  std::vector<int> ladder(n);// = {-1, -2, -2, -1, -1, 3, -1, -2, 2, -1, -3, -1, 2, -1, 1};
  for (size_t i = 0; i < n; ++i) {
    ist >> ladder[i];
  }

  std::ofstream ost;
  ost.open("ladder.out");
  auto res = dyn_ladder(ladder);
  ost << res;
  return 0;
}
