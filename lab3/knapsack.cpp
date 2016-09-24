#include <iostream>
#include <fstream>

#define OUT

using namespace std;

/** 
 * Задача о ранце, запоминаем выбранные товары для каждого промежуточного объёма рюкзака.
 * 
 * @param target Целевой вес товаров.
 * @param n_goods Количество товаров.
 * @param weights Веса товаров.
 * @param costs Стоимость товаров.
 * @param selected_goods Выбранные товары для каждого веса w \in 1, 2, ..., target.
 * @param opt_costs Найденные максимальные стоимости товаров для каждого веса w \in 1, 2, ..., target.
 */
void knapsack1(int target, int n_goods, short *weights, short *costs,
	       OUT int **selected_goods, OUT short *opt_costs)
{
  int optimal_good = 0;
  opt_costs[0] = 0;
  for (int i = 1; i <= target; ++i) {
    int max = 0;
    optimal_good = -1;
    for (int j = 0; j < n_goods; ++j) {
      if (i - weights[j] >= 0 && opt_costs[i - weights[j]] + costs[j] > max) {
	max = opt_costs[i - weights[j]] + costs[j];
	optimal_good = j;
      }
    }

    opt_costs[i] = max;

    for (int j = 0; j < n_goods; ++j) {
      selected_goods[i][j] = 0;
      if (optimal_good != -1) {
	selected_goods[i][j] += selected_goods[i - weights[optimal_good]][j];
      }
    }
    if (optimal_good != -1) {
      ++selected_goods[i][optimal_good];
    }
  }
}

/** 
 * Задача о ранце, рассчитываем, какие товары нужно положить в рюкзак по найденному их весу.
 * 
 *@param target Целевой вес товаров.
 * @param n_goods Количество товаров.
 * @param weights Веса товаров.
 * @param costs Стоимость товаров.
 * @param selected_goods Выбранные товары для веса target..
 * @param opt_costs Найденные максимальные стоимости товаров для каждого веса w \in 1, 2, ..., target. 
 */
void knapsack2(int target, int n_goods, short *weights, short *costs,
	       OUT int **selected_goods, OUT short *opt_costs)
{
  opt_costs[0] = 0;

  for (int i = 0; i < n_goods; ++i) {
    selected_goods[0][i] = 0;
  }
  
  for (int i = 1; i <= target; ++i) {
    int max = 0;
    for (int j = 0; j < n_goods; ++j) {
      if (i - weights[j] >= 0 && opt_costs[i - weights[j]] + costs[j] > max) {
	max = opt_costs[i - weights[j]] + costs[j];
      }
    }

    opt_costs[i] = max;
  }

  int optimal_good = 0;
  for (int i = target; opt_costs[i] > 0; ) {
    short max = 0;
    for (int j = 0; j < n_goods; ++j) {
      if (i - weights[j] >= 0 && opt_costs[i - weights[j]] + costs[j] > max) {
	max = opt_costs[i - weights[j]] + costs[j];
	optimal_good = j;
      }
    }

    ++selected_goods[1][optimal_good];
    i -= weights[optimal_good];
  }
}

int main(int argc, char *argv[])
{
  int knapsack_version = 1;
  if (argc > 1) {
    knapsack_version = atoi(argv[1]);
  }
  int target;
  int n_goods;
  ifstream ist;
  ist.open("knapsack.in");
  if (!ist) {
    std::cerr << "Cannot open knapsack.in\n";
    return -1;
  }
  
  ist >> n_goods;
  ist >> target;
  short *weights = new short[n_goods];
  short *costs = new short[n_goods];
  int **selected_goods = new int *[target + 1];

  for (int i = 0; i < target + 1; ++i) {
    selected_goods[i] = new int[n_goods];
  }

  for (int i = 0; i < n_goods; ++i) {
    ist >> weights[i];
    selected_goods[0][i] = 0;
  }

  for (int i = 0; i < n_goods; ++i) {
    ist >> costs[i];
  }
  ist.close();
  
  short *opt_costs = new short[target + 1];
  if (1 == knapsack_version) {
    knapsack1(target, n_goods, weights, costs, selected_goods, opt_costs);    
  } else {
    knapsack2(target, n_goods, weights, costs, selected_goods, opt_costs);
  }

  
  ofstream ost;
  ost.open("knapsack.out");
  ost << opt_costs[target] << "\n";
  for (int i = 1; i <= target; ++i) {
    for (int j = 0; j < n_goods; ++j) {
      ost << selected_goods[i][j] << ' ';
    }
    delete[] selected_goods[i];
    ost << std::endl;
  }
  delete[] selected_goods;
  delete[] weights;
  delete[] costs;
  delete[] opt_costs;
  
  return 0;
}
