//  Flyweight Coding Exercise
//  You are given a class called Sentence, which takes a string such as "hello world".You need to provide an interface such that the indexer(operator []) returns a WordToken  that can be used to capitalize a particular word in the sentence.
//
//  Typical use would be something like :
//
//  Sentence sentence("hello world");
//  sentence[1].capitalize = true;
//  cout << sentence.str(); // prints "hello WORLD"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct Sentence
{
  struct WordToken
  {
    bool capitalize = false;
  };

  Sentence(const std::string& text) : sentence(text)
  {
  }

  WordToken& operator[](size_t index)
  {
    tokens[index] = WordToken();
    return tokens.at(index);
  }

  std::string str() const
  {
    int start, end, index;
    start = end = index = 0;
    char dl = ' ';

    while ((start = sentence.find_first_not_of(dl, end)) != std::string::npos) {
      end = sentence.find(dl, start);

      const auto it = tokens.find(index);
      if (it != tokens.end() && it->second.capitalize)
      {
        std::transform(sentence.begin() + start, sentence.end() - end - start, sentence.begin() + start,
          [](unsigned char c) {return std::toupper(c); }
        );
      }

      index++;
    }

    return sentence;
  }

private:
  mutable std::string sentence;
  std::map<size_t, WordToken> tokens;
};

int main()
{
  Sentence sentence("hello world");
  sentence[1].capitalize = true;
  std::cout << sentence.str(); // prints "hello WORLD"
}