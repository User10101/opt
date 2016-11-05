#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  int n = 3, m = 1, k = 5;
  int a = 7, b = 2;
  cin >> n >> m >> k;
  cin >> a >> b;

  int ed_entrance = ceil((float)a / (float)(m * k));
  int nat_entrance = ceil((float)b / (float)(m * k));

  int ed_floor = ceil((float)(a - (ed_entrance-1) *
			      m * k) / (float)k);
  int nat_floor = ceil((float)(b - (nat_entrance-1) *
			       m * k) / (float)k);

  if (ed_entrance == nat_entrance && ed_floor == nat_floor) {
    cout << 0;
  } else if (ed_entrance == nat_entrance) {
    int dif = abs(ed_floor - nat_floor);
    cout << min(dif*5, 10 + dif);
  } else {
    int et;
    if (abs(ed_entrance - nat_entrance) <= n/2) {
      et = abs(ed_entrance - nat_entrance) * 15;
    } else {
      if (ed_entrance < nat_entrance) {
	et = (ed_entrance + n - nat_entrance) * 15;
      } else {
	et = (nat_entrance + n - ed_entrance) * 15;
      }
    }
    int dif = abs(ed_floor - nat_floor);
    cout << min((ed_floor-1)*5, 10 + ed_floor - 1) + min((nat_floor-1)*5, 10
							 + nat_floor - 1) + et;
  }

  return 0;
}
