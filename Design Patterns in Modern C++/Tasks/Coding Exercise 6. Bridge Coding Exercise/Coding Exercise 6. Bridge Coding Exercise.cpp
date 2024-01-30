// Bridge Coding Exercise
// You are given an example of an inheritance hierarchy which results in Cartesian - product duplication.
//
// Please refactor this hierarchy, giving the base class Shape  an initializer that takes a Renderer  defined as
//
// struct Renderer
// {
//   virtual string what_to_render_as() const = 0;
// }
// as well as VectorRendererand RasterRenderer.
//
// The expectation is that each constructed object has a member called str()  that returns its textual representation, for example,
//
// Triangle(RasterRenderer()).str() // returns "Drawing Triangle as pixels" 

#include <string>
#include <iostream>
using namespace std;

struct Renderer
{
  virtual string what_to_render_as() const = 0;
};

struct VectorRenderer : Renderer
{
  virtual string what_to_render_as() const {
    return " as lines";
  }
};

struct RasterRenderer : Renderer
{
  virtual string what_to_render_as() const {
    return " as pixels";
  }
};

struct Shape
{
  Renderer& renderer;
  string name;
  Shape(Renderer& renderer) :renderer(renderer) {}
  virtual string str() const = 0;

};

struct Triangle : Shape
{
  Triangle(Renderer& renderer) : Shape(renderer)
  {
    name = "Triangle";
  }
  virtual string str() const
  {
    string str = "Drawing " + name + renderer.what_to_render_as();
    return str;
  }
};

struct Square : Shape
{
  Square(Renderer& renderer) : Shape(renderer)
  {
    name = "Square";
  }
  virtual string str() const
  {
    string str = "Drawing " + name + renderer.what_to_render_as();
    return str;
  }

};
// imagine e.g. VectorTriangle/RasterTriangle etc. here

int main()
{
  Triangle t(RasterRenderer()).str();
}