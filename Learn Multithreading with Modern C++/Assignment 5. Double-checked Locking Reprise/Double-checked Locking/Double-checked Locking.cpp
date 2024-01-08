#include <iostream>
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>

class some_type {
  // ...
public:
  some_type() { std::cout << "call ctor" << std::endl; }
  void do_it() { /*...*/ }
};

std::atomic<some_type*> ptr{ nullptr };
std::mutex process_mutex;

void process() {
  if (!ptr)
  {
    std::lock_guard<std::mutex> lk(process_mutex);
    if (!ptr)
    {
      ptr = new some_type;
    }
  }
  some_type* sp = ptr;
  sp->do_it();
}



int main()
{
  process();

  std::vector<std::thread> threads;

  for (unsigned i = 0; i < 100; ++i)
  {
    threads.emplace_back(process);
  }

  for (auto& th : threads)
  {
    th.join();
  }

  return 0;
}
