#include <iostream>
#include <thread>
#include <future>

void calculate(int a, int b, std::promise<int> pr)
{
  pr.set_value(a + b);
}

void display(std::future<int> fut)
{
  std::cout << "Result: " << fut.get();
}

int main()
{
  std::promise<int> pr;
  std::future<int> fut = pr.get_future();

  std::thread thr1(calculate, 2, 3, std::move(pr));
  std::thread thr2(display, std::move(fut));

  thr1.join();
  thr2.join();
}
