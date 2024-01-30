//
// Builder Coding Exercise
// You are asked to implement the Builder design pattern for rendering simple chunks of code.
//
// Sample use of the builder you are asked to create :
//
// auto cb = CodeBuilder{ "Person" }.add_field("name", "string").add_field("age", "int");
// cout << cb;
// The expected output of the above code is :
//
// class Person
// {
//   string name;
//   int age;
// };
// Please observe the same placement of curly bracesand use two - space indentation.

#include <string>
#include <ostream>
#include <iostream>
#include <vector>

class CodeBuilder
{
public:
  CodeBuilder(const std::string& class_name) : ClassName(class_name), SpaceIndentation(2, ' ')
  {
  }

  CodeBuilder& add_field(const std::string& name, const std::string& type)
  {
    Fields.push_back({ name, type });
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj)
  {
    os << "class " << obj.ClassName << "\n{\n";
    for (const auto& field : obj.Fields)
    {
      os << "" << obj.SpaceIndentation << field.second << " " << field.first << ";\n";
    }

    os << "};\n";
    return os;
  }

private:
  std::string ClassName;
  std::vector <std::pair<std::string, std::string>> Fields;
  const std::string SpaceIndentation;
};

int main()
{
  auto cb = CodeBuilder{ "Person" }.add_field("name", "string").add_field("age", "int");
  std::cout << cb;
}