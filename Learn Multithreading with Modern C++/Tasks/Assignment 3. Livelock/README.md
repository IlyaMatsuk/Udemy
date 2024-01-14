A function modifies a shared variable. It is executed concurrently by two threads:

```cpp
int x{0};
 
void func() {
    while (x == 0) {
        x = 1 - x;
    }
}

std::thread thr1{ func };
std::thread thr2{ func };
```

Questions for this assignment:

1. Are there any possible scenarios in which neither thread is able to exit the loop? If so, how could this happen?
2. If so, suggest a way to fix the problem.