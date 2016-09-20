#include <iostream>
#include <fstream>

#define N_GOODS 3

using namespace std;

int main()
{
  int target;
  int N_GOODS;
  ifstream ist;
  ist.open("knapsack.in");
  ist >> N_GOODS;
  ist >> target;
  short weights[N_GOODS];
  short costs[N_GOODS];

  for (size_t i = 0; i < N_GOODS; ++i) {
    ist >> weights[i];
  }

  for (size_t i = 0; i < N_GOODS; ++i) {
    ist >> costs[i];
  }
  ist.open();
  
  short opt_costs[target];
  int curr_weight = 0;
  int curr_cost = 0;
  for (int i = 0; i < target; ++i) {
    int max = 0;
    for (int j = 0; j < N_GOODS; ++j) {
      if (i - weights[j] >= 0 && opt_costs[i - weights[j]] + costs[j] > max) {
	max = opt_costs[i - weights[j]] + costs[j];
      }
    }

    opt_costs[i] = max;
  }

  ofstream ost;
  ost.open("knapsack.out");
  ost << opt_costs[target - 1] << "\n";
  
  return 0;
}
