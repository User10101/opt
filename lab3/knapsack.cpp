#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  int target;
  int N_GOODS;
  ifstream ist;
  ist.open("knapsack.in");
  if (!ist) {
    std::cerr << "Cannot open knapsack.in\n";
    return -1;
  }
  
  ist >> N_GOODS;
  ist >> target;
  cout << target << "\n";
  cout << N_GOODS << "\n";
  short weights[N_GOODS];
  short costs[N_GOODS];
  int selected_goods[target + 1][N_GOODS];

  for (size_t i = 0; i < N_GOODS; ++i) {
    ist >> weights[i];
    selected_goods[0][i] = 0;
  }

  for (size_t i = 0; i < N_GOODS; ++i) {
    ist >> costs[i];
  }
  ist.close();
  
  short opt_costs[target + 1];
  int curr_weight = 0;
  int curr_cost = 0;
  int selected_ind = 0;
  opt_costs[0] = 0;
  for (int i = 1; i <= target; ++i) {
    int max = 0;
    selected_ind = -1;
    for (int j = 0; j < N_GOODS; ++j) {
      if (i - weights[j] >= 0 && opt_costs[i - weights[j]] + costs[j] > max) {
	max = opt_costs[i - weights[j]] + costs[j];
	selected_ind = j;
      }
    }

    opt_costs[i] = max;
    if (selected_ind != -1) {
      for (int j = 0; j < N_GOODS; ++j) {
	selected_goods[i][j] = 0;
	selected_goods[i][j] += selected_goods[i - weights[selected_ind]][j];
      }
      ++selected_goods[i][selected_ind]; 
    }
  }

  ofstream ost;
  ost.open("knapsack.out");
  ost << opt_costs[target] << "\n";
  for (int i = 1; i <= target; ++i) {
    for (int j = 0; j < N_GOODS; ++j) {
      ost << selected_goods[i][j] << ' ';
    }
    ost << std::endl;
  }
  
  return 0;
}
