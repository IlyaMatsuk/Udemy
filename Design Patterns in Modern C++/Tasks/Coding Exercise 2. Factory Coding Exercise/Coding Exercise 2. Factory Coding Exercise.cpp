//  Factory Coding Exercise
//  You are given a class called Person.The person has two fields : id, and name .
//
//  Please implement a non - static PersonFactory that has a create_person()  method that takes a person's name.
//
//  The id  of the person should be set as a 0 - based index of the object created.So, the first person the factory makes should have id = 0, second id = 1 and so on.

#include <iostream>

#include <string>

struct Person
{
  int id{0};
  std::string name;
};

class PersonFactory
{
public:
  Person create_person(const std:: string& name)
  {
    Person person;
    person.name = name;
    person.id = id++;
    return person;
  }

private:
  int id{ 0 };
};

int main()
{
  PersonFactory pf;
  const auto p1 = pf.create_person("Ilya");
  const auto p2 = pf.create_person("Ira");
  std::cout << "p1: " << p1.id << " " << p1.name << std::endl;
  std::cout << "p2: " << p2.id << " " << p2.name << std::endl;
}
