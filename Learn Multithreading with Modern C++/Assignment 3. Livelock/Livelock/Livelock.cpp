#include <thread>
#include <mutex>

int x{ 0 };
std::mutex mt;

void func() {
  while (x == 0) {
    std::lock_guard<std::mutex> lck(mt);
    if (!x)
    {
      x = 1 - x;
    }
  }
}

int main()
{
  std::thread thr1{ func };
  std::thread thr2{ func };

  thr1.join();
  thr2.join();
}