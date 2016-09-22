#include <iostream>
#include <fstream>

using namespace std;

/** 
 * Задача о ранце, запоминаем выбранные товары для каждого промежуточного объёма рюкзака.
 * 
 * @param target Целевой вес товаров.
 * @param N_GOODS Количество товаров.
 * @param weights Веса товаров.
 * @param costs Стоимость товаров.
 * @param selected_goods Выбранные товары для каждого веса w \in 1, 2, ..., target.
 * @param opt_costs Найденные максимальные стоимости товаров для каждого веса w \in 1, 2, ..., target.
 */
void knapsack1(int target, int N_GOODS, short *weights, short *costs,
	       int **selected_goods, short *opt_costs)
{
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

    for (int j = 0; j < N_GOODS; ++j) {
      selected_goods[i][j] = 0;
      if (selected_ind != -1) {
	selected_goods[i][j] += selected_goods[i - weights[selected_ind]][j];
      }
    }
    if (selected_ind != -1) {
      ++selected_goods[i][selected_ind];
    }
  }
}

/** 
 * Задача о ранце, рассчитываем, какие товары нужно положить в рюкзак по найденному их весу.
 * 
 *@param target Целевой вес товаров.
 * @param N_GOODS Количество товаров.
 * @param weights Веса товаров.
 * @param costs Стоимость товаров.
 * @param selected_goods Выбранные товары для веса target..
 * @param opt_costs Найденные максимальные стоимости товаров для каждого веса w \in 1, 2, ..., target. 
 */
void knapsack2(int target, int N_GOODS, short *weights, short *costs,
	       int **selected_goods, short *opt_costs)
{
  int curr_weight = 0;
  int curr_cost = 0;
  opt_costs[0] = 0;
  for (int i = 1; i <= target; ++i) {
    int max = 0;
    for (int j = 0; j < N_GOODS; ++j) {
      if (i - weights[j] >= 0 && opt_costs[i - weights[j]] + costs[j] > max) {
	max = opt_costs[i - weights[j]] + costs[j];
      }
    }

    opt_costs[i] = max;
    
}

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
  int **selected_goods = new int *[target + 1];

  for (size_t i = 0; i < target + 1; ++i) {
    selected_goods[i] = new int[N_GOODS];
  }

  for (size_t i = 0; i < N_GOODS; ++i) {
    ist >> weights[i];
    selected_goods[0][i] = 0;
  }

  for (size_t i = 0; i < N_GOODS; ++i) {
    ist >> costs[i];
  }
  ist.close();
  
  short opt_costs[target + 1];
  knapsack1(target, N_GOODS, weights, costs, selected_goods, opt_costs);
  
  ofstream ost;
  ost.open("knapsack.out");
  ost << opt_costs[target] << "\n";
  for (int i = 1; i <= target; ++i) {
    for (int j = 0; j < N_GOODS; ++j) {
      ost << selected_goods[i][j] << ' ';
    }
    delete[] selected_goods[i];
    ost << std::endl;
  }
  delete[] selected_goods;
  
  return 0;
}
