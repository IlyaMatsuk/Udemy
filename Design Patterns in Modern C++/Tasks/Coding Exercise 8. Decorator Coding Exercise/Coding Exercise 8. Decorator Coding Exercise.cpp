//  Decorator Coding Exercise
//  Roses can be red, blue or red and blue.
//  Given the class interface Flowerand class Rose, build decorators RedFlowerand BlueFlower that would print the following :
//
//  Rose rose;
//  RedFlower red_rose{ rose };
//  RedFlower red_red_rose{ red_rose };
//  BlueFlower blue_red_rose{ red_rose };
//  cout << rose.str();          // "A rose"
//  cout << red_rose.str();      // "A rose that is red"
//  cout << red_red_rose.str();  // "A rose that is red"
//  cout << blue_red_rose.str(); // "A rose that is red and blue"

#include <string>
using namespace std;

struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
  string str() override {
    return "A rose";
  }
};

struct RedFlower : Flower
{
  Flower& fl;
  string color = "red";
  RedFlower(Flower& f) : fl(f)
  {
  }

  string str() override
  {
    string ret = fl.str();
    if (ret.find("that is") == string::npos)
      ret += " that is " + color;
    else if (ret.find(color) == string::npos)
      ret += " and " + color;
    return ret;
  }
};

struct BlueFlower : Flower
{
  Flower& fl;
  string color = "blue";
  BlueFlower(Flower& f) : fl(f)
  {
  }

  string str() override
  {
    string ret = fl.str();
    if (ret.find("that is") == string::npos)
      ret += " that is " + color;
    else if (ret.find(color) == string::npos)
      ret += " and " + color;
    return ret;
  }
};