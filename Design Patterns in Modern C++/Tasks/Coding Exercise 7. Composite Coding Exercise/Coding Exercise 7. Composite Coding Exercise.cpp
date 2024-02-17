
//  Composite Coding Exercise
//  Consider the code presented below.The sum()  function takes a vector of pointers to either SingleValue or ManyValues instances and adds up all their elements together.
//
//  Please complete the implementation so that the sum()  function starts to operate correctly.This may involve giving the classes a common interface, among other things.
//
//  Here is an example of how the function might be used :
//
//  SingleValue single_value{ 1 };
//  ManyValues other_values;
//  other_values.add(2);
//  other_values.add(3);
//  sum({ &single_value, &other_values }); // returns 6

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ContainsIntegers
{
public:
  virtual int sum() = 0;
};

struct SingleValue : public ContainsIntegers
{
  int value{ 0 };
  SingleValue() = default;

  explicit SingleValue(const int value)
    : value{ value }
  {
  }

  int sum() { return value; }

  SingleValue* begin() { return this; }
  SingleValue* end() { return this + 1; }
};

struct ManyValues : vector<int>, public ContainsIntegers
{
  void add(const int value)
  {
    push_back(value);
  }

  int sum()
  {
    int acc = 0;
    for (auto e : *this)
      acc += e;
    return acc;

  }
};

int sum(const vector<ContainsIntegers*> items);

// #include "exercise.h"

int sum(const vector<ContainsIntegers*> items)
{
  int sum = 0;
  for (auto e : items)
    sum += e->sum();
  return sum;
}

int main()
{
  SingleValue single_value{ 1 };
  ManyValues other_values;
  other_values.add(2);
  other_values.add(3);
  std::cout << sum({ &single_value, &other_values });
}