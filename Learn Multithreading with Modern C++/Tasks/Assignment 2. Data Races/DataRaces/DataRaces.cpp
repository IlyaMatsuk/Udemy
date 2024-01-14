#include <iostream>
#include <vector>
#include <thread>

int global = 0;

void IncrementGlobalVariable()
{
  for (; global < 10000; ++global){}
}

int main()
{
  std::vector<std::thread> threads;

  for (size_t i = 0; i < 10; ++i)
  {
    threads.emplace_back(IncrementGlobalVariable);
  }

  for (auto& thread : threads)
  {
    thread.join();
  }

  std::cout << "Global variable: " << global << std::endl;

  return 0;
}