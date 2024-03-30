Str/*ategy Coding Exercise
Consider the quadratic equationand its canonical solution :

The part b ^ 2 - 4 * a * c is called the discriminant.Suppose we want to provide an API with two different strategies for calculating the discriminant :

In OrdinaryDiscriminantStrategy, If the discriminant is negative, we return it as - is.This is OK, since our main API returns std::complex  numbers anyway.
In RealDiscriminantStrategy, if the discriminant is negative, the return value is NaN(not a number).NaN propagates throughout the calculation, so the equation solver gives two NaN values.
Please implement both of these strategies as well as the equation solver itself.With regards to plus - minus in the formula, please return the + result as the first element and -as the second.*/

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cmath>
using namespace std;

struct DiscriminantStrategy
{
  virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
  double calculate_discriminant(double a, double b, double c) override
  {
    return b * b - 4 * a * c;
  }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
  // todo
  double calculate_discriminant(double a, double b, double c) override
  {
    double ret = b * b - 4 * a * c;
    return ret < 0 ? NAN : ret;
  }
};

class QuadraticEquationSolver
{
  DiscriminantStrategy& strategy;
public:
  QuadraticEquationSolver(DiscriminantStrategy& strategy) : strategy(strategy) {}

  tuple<complex<double>, complex<double>> solve(double a, double b, double c)
  {
    // todo
    double discri = strategy.calculate_discriminant(a, b, c);
    double x1_real = 0.f, x1_imag = 0.f;
    double x2_real = 0.f, x2_imag = 0.f;
    double denominator = 2 * a;

    x1_real = x2_real = isnan(discri) ? NAN : -(b / denominator);
    x1_imag = sqrt(abs(discri)) / denominator;
    x2_imag = -(x1_imag);

    if (discri > 0)
      return make_tuple(complex<double>{x1_real + x1_imag, 0}, complex<double>{x2_real + x2_imag, 0});
    else
      return make_tuple(complex<double>{x1_real, x1_imag}, complex<double>{x2_real, x2_imag});
  }
};


int main()
{
    std::cout << "Hello World!\n";
}