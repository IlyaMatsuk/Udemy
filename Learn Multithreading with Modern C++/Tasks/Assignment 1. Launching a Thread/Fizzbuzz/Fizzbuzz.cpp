#include <iostream>
#include <thread>

void LaunchFizzBuzzGame(size_t numberOfChildren)
{
  for (size_t i = 1; i <= numberOfChildren; ++i) {
    if (i % 3 == 0 && i % 5 == 0) {
      std::cout << "FizzBuzz" << std::endl;
    }
    else if (i % 3 == 0) {
      std::cout << "Fizz" << std::endl;
    }
    else if (i % 5 == 0) {
      std::cout << "Buzz" << std::endl;
    }
    else {
      std::cout << i << std::endl;
    }
  }
}


int main()
{
  size_t numberOfChildren{ 0 };
  std::cout << "Enter the number of children: ";
  std::cin >> numberOfChildren;

  std::thread th{ LaunchFizzBuzzGame,  numberOfChildren };

  th.join();

  return 0;
}
