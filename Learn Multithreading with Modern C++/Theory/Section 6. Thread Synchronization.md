dates:: 2024-01-13 16:32

---

Context:
- [Thread Coordination](#Thread%20Coordination)
- [std condition_variable](#std%20condition_variable)
- [std future](#std%20future)
- [std shared_future](#std%20shared_future)
- [std promise](#std%20promise)

---
### Thread Coordination

Thread coordination is the management of the execution flow and synchronization between multiple threads in a concurrent program. Coordination ensures that threads work together harmoniously to achieve a specific goal or to prevent conflicts that may arise from concurrent access to shared resources. Common mechanisms for thread coordination include synchronization primitives, such as mutexes, condition variables, semaphores, and barriers.

Here are some key aspects of thread coordination:

1. **Mutual Exclusion:**
   - Ensures that only one thread at a time can access a shared resource. Mutexes (mutual exclusion locks) are commonly used to achieve mutual exclusion.

2. **Synchronization:**
   - Ensures that threads proceed in a specific order or at specific points in their execution. Synchronization mechanisms, such as condition variables, can be used to coordinate the execution of threads.

3. **Communication:**
   - Enables communication between threads, allowing them to exchange information or signal events. Condition variables and inter-thread communication mechanisms facilitate communication.

4. **Deadlock Avoidance:**
   - Involves strategies to prevent deadlocks, such as using a consistent order when acquiring multiple locks or limiting the time a thread can hold a lock.

5. **Livelock Avoidance:**
   - Involves strategies to prevent livelocks, such as introducing randomness or timeouts in decision-making processes to break cycles.

Common Thread Coordination Mechanisms:

1. **Mutex (Locks):**
   - Used to achieve mutual exclusion by allowing only one thread to access a critical section at a time.

2. **Condition Variables:**
   - Allow threads to wait for a specific condition to become true before proceeding. They are often used in conjunction with mutexes.

3. **Semaphores:**
   - Control access to a resource by maintaining a count of available resources. Semaphores can be used for synchronization and limiting concurrency.

4. **Barriers:**
   - Synchronize a group of threads by forcing them to wait until all threads have reached a certain point in their execution before continuing.

5. **Atomic Operations:**
   - Use atomic operations to perform certain operations without the need for locks, suitable for simple, fine-grained synchronization.

6. **Thread Pools:**
   - Organize threads into a pool to efficiently manage and reuse threads, reducing the overhead of thread creation.

7. **Futures and Promises:**
   - Allow threads to coordinate and exchange values by sharing the result of a computation between them.

8. **Message Passing:**
   - Threads communicate by sending messages to each other. This can be achieved using various inter-thread communication mechanisms.

Effective thread coordination is crucial for developing robust and scalable concurrent programs. It requires a good understanding of the shared resources, potential conflicts, and careful application of synchronization mechanisms to ensure proper interaction between threads.

### std::condition_variable

`std::condition_variable` is a synchronization primitive in C++ that allows threads to efficiently wait for a specific condition to be satisfied. It is typically used in conjunction with a `std::mutex` to enable multiple threads to coordinate their activities based on changes to shared data.

Here are the key aspects of `std::condition_variable`:

1. Declaration:
   - Include the `<condition_variable>` header to use `std::condition_variable`.

   ```cpp
   #include <condition_variable>
   ```

2. Usage with `std::mutex`:
   - `std::condition_variable` is often used with a `std::mutex` to protect shared data.

   ```cpp
   std::mutex mutex;
   std::condition_variable cv;
   ```

3. Waiting:
   - A thread can wait on a condition variable until a condition is met.

   ```cpp
   std::unique_lock<std::mutex> lock(mutex);
   cv.wait(lock);  // Releases the lock and waits for a notification.
   ```

4. Notification:
   - Threads can notify each other when a condition is satisfied using `notify_one` or `notify_all`.

   ```cpp
   cv.notify_one();  // Notify one waiting thread.
   cv.notify_all();  // Notify all waiting threads.
   ```

5. Predicates:
   - Condition variables are often used with a predicate, which is a function that checks if the condition is satisfied. This helps avoid spurious wake-ups.

   ```cpp
   std::unique_lock<std::mutex> lock(mutex);
   cv.wait(lock, []() { return condition; });
   ```

Example:

Here's a simple example demonstrating the use of `std::condition_variable`:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;
bool dataReady = false;

void producer() {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        std::lock_guard<std::mutex> lock(mutex);
        dataReady = true;
        std::cout << "Data produced.\n";
    }

    cv.notify_one();  // Notify the waiting thread
}

void consumer() {
    std::unique_lock<std::mutex> lock(mutex);

    // Wait until data is ready
    cv.wait(lock, []() { return dataReady; });

    // Process the data
    std::cout << "Data consumed.\n";
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
```

In this example, the `consumer` thread waits for the `producer` thread to set `dataReady` to `true` before proceeding. The condition variable (`cv`) is used to signal the waiting thread when the condition is met. Note the use of the `std::unique_lock` to lock and unlock the mutex automatically. The lambda function in the `cv.wait` call serves as a predicate to avoid spurious wake-ups.

### std::future

`std::future` is a part of the C++ Standard Library introduced in C++11, and it is a mechanism for interacting with the result of asynchronous operations. It represents a value or an exception that will be available at some point in the future. `std::future` is typically used with asynchronous tasks and futures/promises mechanism.

Here are the key aspects of `std::future`:

1. Declaration:
   - Include the `<future>` header to use `std::future`.

   ```cpp
   #include <future>
   ```

2. Creating a Future:
   - Use `std::async` or `std::promise` to create a `std::future`.

   ```cpp
   std::future<int> result = std::async(std::launch::async, []() { return 42; });
   ```

3. Retrieving the Result:
   - Use the `get` member function to retrieve the result.

   ```cpp
   int value = result.get();
   ```

   - The `get` function will block until the result is ready.

4. Exception Handling:
   - If an exception occurred during the asynchronous operation, it will be propagated when calling `get`.

   ```cpp
   try {
       int value = result.get();
   } catch (const std::exception& e) {
       std::cerr << "Exception caught: " << e.what() << std::endl;
   }
   ```

5. Validity Check:
   - Use the `valid` member function to check if the `std::future` holds a shared state (result or exception).

   ```cpp
   if (result.valid()) {
       // The future has a shared state
   }
   ```

6. Waiting for the Result:
   - Instead of blocking with `get`, you can use `wait` to wait for the result to become available.

   ```cpp
   result.wait();  // Non-blocking
   ```

Example:

Here's a simple example demonstrating the use of `std::future`:

```cpp
#include <iostream>
#include <future>

int main() {
    std::future<int> result = std::async(std::launch::async, []() {
        // Simulate some time-consuming computation
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 42;
    });

    std::cout << "Waiting for the result...\n";

    // Wait for the result (blocking)
    int value = result.get();

    std::cout << "Result: " << value << std::endl;

    return 0;
}
```

In this example, an asynchronous task is created using `std::async`, and the result is obtained using `get`. The program will wait for the result to be ready before printing it. Note that `std::async` launches a new thread to perform the computation asynchronously.
### std::shared_future

`std::shared_future` is a part of the C++ Standard Library introduced in C++11, and it is used in conjunction with `std::future` to represent a shared state for retrieving the result of an asynchronous operation. Unlike `std::future`, `std::shared_future` can be copied and shared among multiple threads, allowing multiple threads to independently wait for the result.

Here are the key aspects of `std::shared_future`:

1. Declaration:
   - Include the `<future>` header to use `std::shared_future`.

   ```cpp
   #include <future>
   ```

2. Creating a `std::shared_future`:
   - Obtain a `std::shared_future` from a `std::future` using the `share` member function.

   ```cpp
   std::future<int> futureResult = std::async(std::launch::async, []() { return 42; });
   std::shared_future<int> sharedResult = futureResult.share();
   ```

3. Retrieving the Result:
   - Use the `get` member function to retrieve the result.

   ```cpp
   int value = sharedResult.get();
   ```

   - Multiple threads can independently call `get` on a shared future.

Example:

Here's a simple example demonstrating the use of `std::shared_future`:

```cpp
#include <iostream>
#include <future>

void printResult(std::shared_future<int> sharedResult) {
    // Wait for the result and print it
    int value = sharedResult.get();
    std::cout << "Result from thread: " << value << std::endl;
}

int main() {
    std::future<int> futureResult = std::async(std::launch::async, []() {
        // Simulate some time-consuming computation
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 42;
    });

    // Create a shared future from the original future
    std::shared_future<int> sharedResult = futureResult.share();

    // Start multiple threads to print the result independently
    std::thread thread1(printResult, sharedResult);
    std::thread thread2(printResult, sharedResult);

    // Wait for the threads to finish
    thread1.join();
    thread2.join();

    return 0;
}
```

In this example, `std::async` is used to create a `std::future`, and `share` is used to obtain a `std::shared_future`. Multiple threads are then started to independently wait for and print the result using `get` on the shared future. The shared future ensures that the result can be accessed by multiple threads without blocking or duplicating the computation.
### std::promise

`std::promise` is another component of the C++ Standard Library introduced in C++11, and it is often used in conjunction with `std::future` to facilitate communication between threads. It represents a single-use communication channel between the asynchronous task (producer) and the future (consumer) that will eventually retrieve the result or exception.

Here are the key aspects of `std::promise`:

1. Declaration:
   - Include the `<future>` header to use `std::promise`.

   ```cpp
   #include <future>
   ```

2. Creating a Promise:
   - Create a `std::promise` object, and obtain a `std::future` associated with it.

   ```cpp
   std::promise<int> resultPromise;
   std::future<int> resultFuture = resultPromise.get_future();
   ```

3. Setting the Result:
   - Use the `set_value` member function to set the result value.

   ```cpp
   resultPromise.set_value(42);
   ```

4. Setting an Exception:
   - Use the `set_exception` member function to set an exception.

   ```cpp
   try {
       // Some operation that may throw an exception
   } catch (...) {
       resultPromise.set_exception(std::current_exception());
   }
   ```

5. Retrieving the Result from the Future:
   - Use the `get` member function on the associated `std::future` to retrieve the result.

   ```cpp
   int value = resultFuture.get();
   ```

Example:

Here's a simple example demonstrating the use of `std::promise`:

```cpp
#include <iostream>
#include <future>

void asynchronousTask(std::promise<int>& resultPromise) {
    // Simulate some time-consuming computation
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Set the result value
    resultPromise.set_value(42);
}

int main() {
    std::promise<int> resultPromise;
    std::future<int> resultFuture = resultPromise.get_future();

    // Start an asynchronous task
    std::thread taskThread(asynchronousTask, std::ref(resultPromise));

    std::cout << "Waiting for the result...\n";

    // Wait for the result (blocking)
    int value = resultFuture.get();

    // Join the asynchronous task thread
    taskThread.join();

    std::cout << "Result: " << value << std::endl;

    return 0;
}
```

In this example, a `std::promise` is used to communicate the result of an asynchronous task to the main thread. The asynchronous task is simulated using a separate thread, and the result is set using `set_value`. The main thread then waits for the result using `get` on the associated `std::future`.


--- 


## Links

<- Back to [Main](../README.md)