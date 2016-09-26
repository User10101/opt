#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#define FORBIDDEN -101
#define STDIO

using namespace std;

inline int max(int x1, int x2)
{
  if (x1 == FORBIDDEN && x2 == FORBIDDEN) {
    return 0;
  } else if (x1 == FORBIDDEN) {
    return x2;
  } else if (x2 == FORBIDDEN) {
    return x1;
  } else {
    return x1 > x2 ? x1 : x2;
  }
}
  
int main(int argc, char *argv[])
{
  int level_count;
  #ifdef STDIO
  cin >> level_count;
  #else
  ifstream ist;
  ist.open("slalom.in");
  ist >> level_count;
  #endif
  vector<vector<int>> levels(level_count);
  vector<vector<int>> costs(level_count);
  for (int i = 0; i < level_count; ++i) {
    levels[i] = vector<int>(i + 1);
    costs[i] = vector<int>(i + 1);
    for (int j = 0; j < levels[i].size(); ++j) {
      #ifdef STDIO
      cin >> levels[i][j];
      #else
      ist >> levels[i][j];
      #endif
      
      if (i - 1 >= 0) {
	int opt1 = FORBIDDEN, opt2 = FORBIDDEN;
	if (j < levels[i - 1].size()) {
	  opt1 = costs[i - 1][j] + levels[i][j];
	  if (j - 1 >= 0) {
	    opt2 = costs[i - 1][j - 1] + levels[i][j];
	  }
	} else {
	  opt1 = costs[i - 1][j - 1] + levels[i][j];
	}
	costs[i][j] = max(opt1, opt2);
      } else {
	costs[i][j] = levels[i][j];
      }
    }
  }

  #ifndef STDIO
  ist.close();
  #endif

  cout << *max_element(costs[costs.size() - 1].begin(), costs[costs.size() - 1].end());

  return 0;
}
