#include <iostream>
#include <climits>
#include <cmath>

inline double abs(double x)
{
  return (x >= 0) ? x : -x;
}

inline double f(double x)
{
  return pow(x - 2, 2);
}

double g(double x, double y)
{
  return 4*x*x + 5*x + 3*x*y + 4*y + y*y;
  //return x*x + 4*x + y*y + 6*y;
  //return 4*x*x - x*y + y * y - 4*x;
  //return pow(x*x - y, 2) + pow(y - 0.6, 2);
}

double min_opt(double x, double a = -1000, double b = 1000, double epsilon = 0.001)
{
  double phi = (1 + sqrt(5)) / 2;
  double x1 = b - (b - a) / phi;
  double x2 = a + (b - a) / phi;
  double y1 = g(x, x1);
  double y2 = g(x, x2);
  while (abs(b - a) >= epsilon) {
    if (y1 >= y2) {
      a = x1;
      x1 = x2;
      y1 = y2;
      x2 = a + (b - a) / phi;
      y2 = g(x, x2);
    } else {
      b = x2;
      x2 = x1;
      y2 = y1;
      x1 = b - (b - a) / phi;
      y1 = g(x, x1);
    }
  }

  return (a + b) / 2;
}

std::pair<double, double> min_tern(double a, double b, double c, double d, double epsilon)
{
  double phi = (1 + sqrt(5)) / 2;
  double x1 = b - (b - a) / phi;
  double my1 = min_opt(x1, c, d, epsilon);
  double x2 = a + (b - a) / phi;
  double my2 = min_opt(x2, c, d, epsilon);
  double g1 = g(x1, my1);
  double g2 = g(x2, my2);
  while (abs(b - a) >= epsilon) {
    if (g1 >= g2) {
      a = x1;
      x1 = x2;
      my1 = my2;
      g1 = g2;
      x2 = a + (b - a) / phi;
      my2 = min_opt(x2, c, d, epsilon);
      g2 = g(x2, my2);
    } else {
      b = x2;
      x2 = x1;
      my2 = my1;
      g2 = g1;
      x1 = b - (b - a) / phi;
      my1 = min_opt(x1, c, d, epsilon);
      g1 = g(x1, my1);
    }
  }

  std::cout << a << " " << b << std::endl;
  return std::pair<double, double>((b + a) / 2, (my2 + my1) / 2);
}

int main(int argc, char *argv[])
{
  std::pair<double, double> res = min_tern(-10, 10, -10, 10, 0.0001);
  std::cout << "Min x: " << res.first << "; Min y: " << res.second << "; Min g(x, y): "
	    << g(res.first, res.second) << std::endl;
  //std::cout << min_opt(0, -10, 10, 0.0001);
  return 0;
}
