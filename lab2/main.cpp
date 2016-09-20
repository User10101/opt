#include <iostream>
#include <armadillo>
#include <fstream>

inline double abs_d(double x)
{
  return (x >= 0) ? x : -x;
}

double f(arma::vec x)
{
  return pow(x[0]*x[0] - x[1], 2) + pow(x[1] - 0.6, 2);
  //return x[0]*x[0] - x[0]*x[1] + x[1]*x[1] - 4*x[0] + 3*x[1];
}

double dfx(arma::vec x, double delta)
{
  // double fx = f(x);
  // x[0] = x[0] + delta;
  // double fdx = f(x);
  // return (fdx - fx) / delta;
  return 2*(x[0]*x[0] - x[1])*2*x[0];
}

double dfy(arma::vec x, double delta)
{
  // double fy = f(x);
  // x[1] = x[1] + delta;
  // double fdy = f(x);
  // return (fdy - fy) / delta;
  return -2*pow(x[0]*x[0] - x[1], 2) + 2*(x[1] - 0.6);
}

arma::vec grad(arma::vec x, double delta)
{
  arma::vec res = {dfx(x, delta), dfy(x, delta)};
  return res;
}

double g(double t, arma::vec x, double delta = 0.001)
{
  return f(x - t*grad(x, delta));
}

double min_opt(const arma::vec &x, double delta, double a = -1000, double b = 1000, double epsilon = 0.001)
{
  double phi = (1 + sqrt(5)) / 2;
  double x1 = b - (b - a) / phi;
  double x2 = a + (b - a) / phi;
  double y1 = g(x1, x, delta);
  double y2 = g(x2, x, delta);
  while (abs_d(b - a) >= epsilon) {
    if (y1 >= y2) {
      a = x1;
      x1 = x2;
      y1 = y2;
      x2 = a + (b - a) / phi;
      y2 = g(x2, x, delta);
    } else {
      b = x2;
      x2 = x1;
      y2 = y1;
      x1 = b - (b - a) / phi;
      y1 = g(x1, x, delta);
    }
  }

  return (a + b) / 2;
}

int main()
{
  double epsilon = 0.0000001;
  double delta = 0.001;
  arma::vec x = {1, 1};
  double prev_norm = 10000000;
  double curr_norm = 0;
  std::string fname = "lab2.txt";
  std::ofstream ost;
  ost.open(fname);
  size_t step_num = 0;
  arma::vec prev_x(2);
  arma::vec prev_diff(2);
  arma::vec curr_diff(2);
  while (1) {
    double t = min_opt(x, delta, 0, 100, epsilon);
    x = x - t*grad(x, delta);
    ost << "Step №: " << step_num << std::endl;
    ost << x[0] << ' ' << prev_x[0] << ' ' << (x - prev_x)[0] << std::endl;
    ost << x[1] << ' ' << prev_x[1] << ' ' << (x - prev_x)[1] << std::endl;
    curr_diff = x - prev_x;
    ost << "Dot product: " << dot(curr_diff, prev_diff) << std::endl;
    curr_norm = arma::norm(x);
    ost << abs_d(curr_norm - prev_norm) << std::endl;
    if (abs_d(curr_norm - prev_norm) < epsilon) {
      break;
    }
    prev_norm = curr_norm;
    ++step_num;
    prev_x = x;
    prev_diff = curr_diff;
  }
  ost.close();

  std::cout << x << std::endl;
  std::cout << "f(x): " << f(x) << std::endl;
  return 0;
}
