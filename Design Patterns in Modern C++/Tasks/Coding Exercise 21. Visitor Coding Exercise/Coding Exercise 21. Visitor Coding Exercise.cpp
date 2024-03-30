//Visitor Coding Exercise
//You are asked to implement a double - dispatch visitor called ExpressionPrinter  for printing different mathematical expressions.
// The range of expressions covers additionand multiplication - please put round brackets around addition but not around multiplication!
// Also, please avoid any blank spaces in output.
//
//Example:
//
//Input: AdditionExpression{ Literal{2}, Literal{3} }  --btw, this is pseudocode, you cannot inline those references unfortunately
//Output : (2 + 3)
//Here is the corresponding unit test :
//
//Value v2{ 2 };
//Value v3{ 3 };
//AdditionExpression simple{ v2,v3 };
//ExpressionPrinter ep;
//ep.accept(simple);
//ASSERT_EQ("(2+3)", ep.str());

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct ExpressionVisitor
{
  ostringstream result;
};


struct Expression
{
public:
  virtual void visit(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
public:
  int value;
  Value(int value) : value(value) {}
  void visit(ExpressionVisitor& epv)
  {
    epv.result << value;
  }
};

struct AdditionExpression : Expression
{
  Expression& lhs, & rhs;
  AdditionExpression(Expression& lhs, Expression& rhs) : lhs(lhs), rhs(rhs) {}

  void visit(ExpressionVisitor& epv)
  {
    epv.result << "(";
    lhs.visit(epv);
    epv.result << "+";
    rhs.visit(epv);
    epv.result << ")";
  }
};

struct MultiplicationExpression : Expression
{
  Expression& lhs, & rhs;

  MultiplicationExpression(Expression& lhs, Expression& rhs)
    : lhs(lhs), rhs(rhs) {}

  void visit(ExpressionVisitor& epv)
  {
    lhs.visit(epv);
    epv.result << "*";
    rhs.visit(epv);
  }
};

struct ExpressionPrinter : ExpressionVisitor
{
  void accept(AdditionExpression& expr)
  {
    expr.visit(*this);
  }

  void accept(MultiplicationExpression& expr)
  {
    expr.visit(*this);
  }

  string str() const
  {
    return result.str();
  }
};


// Notice: I don’t know what deep thought the author of this assignment had, but changing the accept and visit methods is a stupid solution

int main() {
  Value v2{ 2 };
  Value v3{ 3 };
  AdditionExpression simple{ v2, v3 };
  ExpressionPrinter ep;
  ep.accept(simple);
  //assert(ep.str() == "(2+3)");
  return 0;
}

