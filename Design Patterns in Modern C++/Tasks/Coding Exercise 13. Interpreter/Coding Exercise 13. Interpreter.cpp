//Interpreter Coding Exercise
//You are asked to write an expression processor for simple numeric expressions with the following constraints :
//
//Expressions use integral values(e.g., "13"), single - letter variables defined in variables, as well as + and -operators only
//There is no need to support braces or any other operations
//If a variable is not found in Variables(or if we encounter a variable with > 1 letter, e.g.ab), the evaluator returns 0 (zero)
//In case of any parsing failure, evaluator returns 0
//Example:
//
//  calculate("1+2+3")  should return 6
//    calculate("1+2+xy")  should return 0
//    calculate("10-2-x")  when x = 3 is in variables should return 5


#include <string>
#include <map>
#include <cctype>
using namespace std;

struct ExpressionProcessor
{
  map<char, int> variables;

  int calculate(const string& expression)
  {
    int result = 0;
    char op = '+';
    bool isVariable = false;

    for (size_t i = 0; i < expression.size(); ++i) {
      char currentChar = expression[i];

      if (isdigit(currentChar)) {
        int num = 0;
        while (i < expression.size() && isdigit(expression[i])) {
          num = num * 10 + (expression[i] - '0');
          ++i;
        }
        --i;
        if (op == '+')
          result += num;
        else if (op == '-')
          result -= num;
        else
          result = num; // if there's only one digit in the expression
      }
      else if (isalpha(currentChar)) {
        if (variables.find(currentChar) != variables.end()) {
          if (op == '+')
            result += variables[currentChar];
          else if (op == '-')
            result -= variables[currentChar];
          else
            result = variables[currentChar]; // if there's only one variable in the expression
        }
        else {
          return 0; // Variable not found, return 0
        }
      }
      else if (currentChar == '+' || currentChar == '-') {
        op = currentChar;
      }
      else {
        return 0; // Invalid character, return 0
      }

      if (currentChar == '-' || currentChar == '+')
        isVariable = false;
      else
        isVariable = true;
    }

    return result;
  }
};
