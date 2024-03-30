//  Flyweight Coding Exercise
//  You are given a class called Sentence, which takes a string such as "hello world".You need to provide an interface such that the indexer(operator []) returns a WordToken  that can be used to capitalize a particular word in the sentence.
//
//  Typical use would be something like :
//
//  Sentence sentence("hello world");
//  sentence[1].capitalize = true;
//  cout << sentence.str(); // prints "hello WORLD"

#include<iostream> 
#include<string>
#include<cstring>
#include<vector>

using namespace std;

struct Sentence
{
public:
  struct WordToken
  {
    bool capitalize = 0;
    string m_token;

    WordToken(const string& word) : m_token{ word } {}

    string custom_str() const 
    {
      string oss;
      if (capitalize == false)
      {
        return m_token;
      }

      for (const auto& symbol : m_token)
      {
        oss += toupper(symbol);
      }
      return oss;
    }
  }; 

  Sentence(const string& input) : m_text(input)
  {
    char* token = strtok((char*)m_text.c_str(), " ");
    while (token)
    {
      m_tokens_db.emplace_back(WordToken{ string(token) });
      token = strtok(NULL, " ");
    }
  }

  WordToken& operator[](size_t index)
  {
    m_tokens_db[index].capitalize = true;
    return m_tokens_db[index];
  }

  string str() const
  {
    string oss;
    for (const auto& tok : m_tokens_db)
    {
      oss += tok.custom_str();
      oss += " ";
    }
    oss.pop_back();
    return oss;
  }

private:
  string m_text;
  vector<WordToken> m_tokens_db;
};

int main()
{
  Sentence sentence("hello world");
  sentence[1].capitalize = true;
  std::cout << sentence.str(); // prints "hello WORLD"
}