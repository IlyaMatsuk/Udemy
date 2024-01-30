//  Given the provided code, you are asked to implement Line::deep_copy()  to perform a deep copy of the current Line  object.
//  Beware memory leaks!

#include <iostream>

struct Point
{
  int x{ 0 }, y{ 0 };

  Point() {}

  Point(const int x, const int y) : x{ x }, y{ y } {}
};

struct Line
{
  Point* start, * end;

  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    Point* s = new Point(start->x, start->y);
    Point* e = new Point(end->x, end->y);
    return { s, e };
  }
};

int main()
{
    std::cout << "Hello World!\n";
}