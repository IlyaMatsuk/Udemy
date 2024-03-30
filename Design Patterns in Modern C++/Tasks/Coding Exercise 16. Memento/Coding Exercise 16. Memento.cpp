//A TokenMachine  is in charge of keeping tokens.
// Each Token  is a reference type with a single numerical value.The machine supports adding tokensand, when it does, it returns a memento representing the state of that system at that given time.
//
//You are asked to fill in the gapsand implement the Memento design pattern for this scenario.
//Pay close attention to the situation where a token is fed in as a smart pointerand its value is subsequently changed on that pointer - you still need to return the correct system snapshot!

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Token
{
  int value;

  Token(int value) : value(value) {}

  // Copy constructor to ensure deep copy of Token objects
  Token(const Token& other) : value(other.value) {}
};

struct Memento
{
  vector<Token> tokens; // Store Token objects directly, not shared pointers

  Memento(const vector<shared_ptr<Token>>& tokens) {
    for (const auto& token : tokens) {
      this->tokens.push_back(*token); // Copy Token objects
    }
  }
};

struct TokenMachine
{
  vector<shared_ptr<Token>> tokens;

  Memento add_token(int value)
  {
    return add_token(make_shared<Token>(value));
  }

  Memento add_token(const shared_ptr<Token>& token)
  {
    tokens.push_back(token);
    return Memento(tokens); // Construct Memento with copies of Token objects
  }

  void revert(const Memento& m)
  {
    tokens.clear(); // Clear existing tokens

    for (const auto& token : m.tokens) {
      tokens.push_back(make_shared<Token>(token)); // Re-add tokens to the machine
    }
  }
};

int main()
{
    std::cout << "Hello World!\n";
}
